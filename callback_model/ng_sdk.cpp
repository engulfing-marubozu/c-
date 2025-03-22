#include "ng_sdk.hpp"
#include "KillSwitch.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <queue>
#include <memory>

ng_sdk::ng_sdk(int poolSize) {
    std::cout << "SDK Initialized!!\n";
    pool = std::make_unique<Threadpool>(*this, poolSize);
}

Threadpool::Threadpool(ng_sdk &ng_sdk, int num_threads) : _num_threads(num_threads) {
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back([this, &ng_sdk]() {
            std::cout << "new thread initialized \n" << std::hash<std::thread::id>()(std::this_thread::get_id()) << " " << sched_getcpu() << "     " << std::endl;
            while (1) {
                std::unique_lock<std::mutex> lock(m);
                cv.wait(lock, [this]() { return !priceStream.empty() || KillSwitch::getInstance().isStopped(); });
                if (KillSwitch::getInstance().isStopped()) {
                    std::cout << "stopping thread " << std::hash<std::thread::id>()(std::this_thread::get_id()) << " " << sched_getcpu() << std::endl;
                    return;
                }
                PriceUpdate priceUpdate = std::move(priceStream.front());
                priceStream.pop();
                std::cout << "pool received a new order and picked by " << std::hash<std::thread::id>()(std::this_thread::get_id()) << " " << sched_getcpu() << "   \n  " << priceUpdate << std::endl;
                ng_sdk.handleOrderUpdate(priceUpdate);
            }
        });
    }
}

Threadpool::~Threadpool() {
    {
        std::lock_guard<std::mutex> lock(m);
        KillSwitch::getInstance().stop();
    }
    cv.notify_all();
    for (auto &thread : threads) {
        if (thread.joinable()) {
            std::cout << "thread stopped" << std::endl;
            thread.join();
        }
    }
    // Clear the priceStream queue
    std::queue<PriceUpdate> empty;
    std::swap(priceStream, empty);
}

void Threadpool::pushPriceToStream(PriceUpdate priceUpdate) {
    std::lock_guard<std::mutex> lock(m);
    priceStream.push(priceUpdate);
    cv.notify_one();
}

void ng_sdk::Subscribe(int instrument, IMarketDataHandler* subscriber) {
    std::cout << "Subscribed instrument " << instrument << std::endl;
    instrument_subscribers_list[instrument].push_back(subscriber);
}

void ng_sdk::handleOrderUpdate(PriceUpdate priceUpdate) {
    publish(priceUpdate);
}

void ng_sdk::priceEvent(long long int instr_id, std::string instr_name, float bid_price, float ask_price) {
    PriceUpdate priceUpdate(instr_id, instr_name, bid_price, ask_price);
    pool->pushPriceToStream(priceUpdate);
}

void ng_sdk::publish(PriceUpdate priceUpdate) {
    for (auto& pair : instrument_subscribers_list) {
        if (cnt % pair.first == 0) {
            std::cout << "publishing to Algo " << pair.first << std::endl;
            for (auto& subscriber : pair.second) {
                subscriber->OnPriceUpdate(priceUpdate);
            }
        }
    }
}
