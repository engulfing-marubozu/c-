#include <atomic>
#include <iostream>
#include <mutex>
#include <condition_variable>       // std::condition_variable
#include <signal.h>                 // signal
#include <sstream>                  // std::stringstream
#include <boost/uuid/uuid_io.hpp>   // boost::uuids::to_string
#include "./sdk/sdk_api.h"

using namespace hgng_sdk;

std::atomic<bool>       g_running{true};
std::atomic<bool>       g_book_download_complete{false};
std::mutex              g_mutex;
std::condition_variable g_cv;

class TestAlgo : public IMarketDataHandler, public IOrderEventsHandler
{
  public:
    explicit TestAlgo(InstrumentPtr instrument) : instrument_(instrument)
    {
        auto ss = std::stringstream{};
        ss << *instrument;
        std::cout << "Instrument: " << ss.str() << std::endl;

        params_.account_id = 2467;
        params_.user_id    = 1423;
        params_.quantity   = 1;
    }

    void StartAndWait()
    {
        std::cout << "Starting..." << std::endl;
        signal(SIGINT, [](int) { g_running = false; }); // handle 'ctrl+c'

        order_           = CreateOrder(instrument_, this);
        subscription_id_ = SubscribeFastAggregateDepth(instrument_, this);

        while (g_running)
        {
            sleep(1);
        }

        std::cout << "Stopping..." << std::endl;

        if (order_ && !order_->IsTerminal())
        {
            order_->SendForceCancel(params_);
            usleep(100); // not really needed
        }

        if (subscription_id_ != 0)
        {
            Unsubscribe(subscription_id_);
        }
    }

  private:
    void SendNewOrAmend()
    {
        if (order_->IsPlaced())
        {
            if (order_->price != params_.price)
            {
                std::cout << "--- Amending order " << order_->order_id << " (price=" << params_.price << ") ---" << std::endl;
                order_->SendAmend(params_);
            }
        }
        else
        {
            std::cout << "--- Placing order " << order_->order_id << " (price=" << params_.price << ") ---" << std::endl;
            order_->SendNew(params_);
        }
    }

    void OnSubscribed(uint64_t handler_id) override final
    {
        std::cout << "Subscribed " << handler_id << std::endl;
    }

    void OnUnsubscribed(uint64_t handler_id) override final
    {
        std::cout << "Unsubscribed " << handler_id << std::endl;
    }
  void OnTrade(const TradeUpdate &trade) override final
    {
    }

    void OnPrice(const PriceUpdate &price) override final
    {
        RWSpinLock::ReadHolder lock(&lock_);

        if (params_.side == Order::Side::SIDE_SELL)
        {
            if (price.ask_price)
            {
                params_.price = price.ask_price.value();
                SendNewOrAmend();
            }
        }
        else
        {
            if (price.bid_price)
            {
                params_.price = price.bid_price.value();
                SendNewOrAmend();
            }
        }
    }

    void OnOrderEvent(const OrderEvent &event) override final
    {
        if (boost::uuids::to_string(event.order_id) != order_->order_id)
            return;

        if (order_->state == State::FILLED)
        {
            RWSpinLock::WriteHolder lock(&lock_);
            order_->Reset();

            if (params_.side == Order::Side::SIDE_SELL)
            {
                params_.side = Order::Side::SIDE_BUY;
            }
            else
            {
                params_.side = Order::Side::SIDE_SELL;
                if (event.trade_price)
                {
                    params_.price = event.trade_price.value();
                    order_->SendNew(params_);
                }
                else
                {
                    std::cerr << "Trade price not available" << std::endl;
                    g_running = false;
                }
            }
        }
        else if (order_->state == State::CANCELED)
        {
            std::cout << "Order cancelled, stopping the algo" << std::endl;
            g_running = false;
        }
    }

    void OnReject(const OrderEvent &event) override final
    {
        std::cerr << "Order rejected, order_id=" << boost::uuids::to_string(event.order_id) << std::endl;
        if (order_->state == State::REJECTED)
        {
            RWSpinLock::WriteHolder lock(&lock_);
            order_->Reset();
        }
    }

    void OnSendFailed(const std::string &status) override final
    {
        std::cerr << "Send failed: " << status << std::endl;
    }

    void OnBookDownloadComplete(const std::vector<OrderPtr> &orders, const std::vector<AseOrderPtr> &ase_orders) override final
    {
        std::cout << "OBDL complete, total orders=" << orders.size() << ", total ase orders=" << ase_orders.size() << std::endl;
        g_book_download_complete = true;
        book_downloaded_successfully = true;
        g_cv.notify_one();
    }

    void OnBookDownloadFailed(const std::string &error) override final
    {
        std::cerr << "Order book download failed, error: " << error << std::endl;
        g_book_download_complete = true;
        book_downloaded_successfully = false;
        g_cv.notify_one();
    }
  void OnFastAggregateDepth(const FastAggregateDepthUpdate &depth) override final
    {
    }
  public:
    bool book_downloaded_successfully{false};

  private:
    OrderPtr order_;
    InstrumentPtr instrument_;
    OrderParams params_;
    uint64_t subscription_id_{0};
    bool exit_order_ = false;
    using RWSpinLock = folly::RWTicketSpinLockT<32, true>;
    RWSpinLock lock_;
};

int main()
{
    Initialize();
    std::cout << "SDK Initialized..." << std::endl;

    std::string s;
    do
    {
        std::cin >> s;
        if (s == "start")
            break;
    } while (true);

    auto instrument = GetInstrument(4975733391391290516u);
    if (!instrument)
    {
        std::cerr << "Instrument not found" << std::endl;
        Shutdown();
        return 1;
    }

    auto algo = TestAlgo(instrument);

    SubscribeOrderEvents({2467}, &algo, true);

    {
        auto timeout = std::chrono::high_resolution_clock::now() + std::chrono::seconds(10);
        std::unique_lock<std::mutex> lock(g_mutex);
        g_cv.wait_until(lock, timeout, []() { return g_book_download_complete.load(); });
        if (!algo.book_downloaded_successfully)
        {
            std::cerr << "Order book download failed" << std::endl;
            Shutdown();
            return 1;
        }
    }

    algo.StartAndWait();

    std::cout << "Shutting down..." << std::endl;
    Shutdown();
    return 0;
}
