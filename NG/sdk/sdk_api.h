#ifndef MAIN_H
#define MAIN_H

#include <memory>
#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include <chrono>
#include <thread>

// Boost UUID includes for generating and printing dummy UUIDs.
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace hgng_sdk {

// Define a common enum for order side.
enum class Side {
    SIDE_BUY,
    SIDE_SELL
};

// Dummy types for market data and order events updates.
struct TradeUpdate {
    // Add dummy fields if needed.
};

struct PriceUpdate {
    std::optional<double> ask_price;
    std::optional<double> bid_price;
};

struct FastAggregateDepthUpdate {
    // Add dummy fields if needed.
};

struct OrderEvent {
    boost::uuids::uuid order_id;
    std::optional<double> trade_price;
};

struct AseOrder {
    // Dummy ASE order definition.
};

using AseOrderPtr = std::shared_ptr<AseOrder>;

// Instrument definition.
struct Instrument {
    uint64_t id{0};
};

// Overload operator<< for Instrument.
inline std::ostream& operator<<(std::ostream& os, const Instrument& instrument) {
    os << "Instrument(id=" << instrument.id << ")";
    return os;
}

using InstrumentPtr = std::shared_ptr<Instrument>;

// OrderParams structure.
struct OrderParams {
    int account_id{};
    int user_id{};
    int quantity{};
    double price{};
    Side side = Side::SIDE_BUY;
};

// State enum for order status.
enum class State {
    NEW,
    PLACED,
    FILLED,
    CANCELED,
    REJECTED
};

// Order class definition.
class Order {
public:
    // Alias the common Side enum for usage as Order::Side.
    using Side = hgng_sdk::Side;

    std::string order_id; // Dummy order id as a string.
    double price{0.0};
    State state{State::NEW};

    Order() {
        // Generate a dummy UUID for the order_id.
        boost::uuids::random_generator gen;
        order_id = boost::uuids::to_string(gen());
    }

    bool IsTerminal() const {
        return (state == State::FILLED || state == State::CANCELED || state == State::REJECTED);
    }

    bool IsPlaced() const {
        return (state == State::PLACED);
    }

    void Reset() {
        state = State::NEW;
    }

    void SendForceCancel(const OrderParams&) {
        state = State::CANCELED;
        std::cout << "Force cancel sent for order " << order_id << std::endl;
    }

    void SendAmend(const OrderParams& params) {
        price = params.price;
        state = State::PLACED;
        std::cout << "Order " << order_id << " amended to price " << price << std::endl;
    }

    void SendNew(const OrderParams& params) {
        price = params.price;
        state = State::PLACED;
        std::cout << "New order " << order_id << " sent with price " << price << std::endl;
    }
};

using OrderPtr = std::shared_ptr<Order>;

// Interface for handling market data updates.
class IMarketDataHandler {
public:
    virtual ~IMarketDataHandler() = default;
    virtual void OnTrade(const TradeUpdate &trade) = 0;
    virtual void OnPrice(const PriceUpdate &price) = 0;
    virtual void OnFastAggregateDepth(const FastAggregateDepthUpdate &depth) = 0;
    virtual void OnSubscribed(uint64_t handler_id) = 0;
    virtual void OnUnsubscribed(uint64_t handler_id) = 0;
    virtual void OnBookDownloadComplete(const std::vector<OrderPtr>& orders,
                                        const std::vector<AseOrderPtr>& ase_orders) = 0;
    virtual void OnBookDownloadFailed(const std::string &error) = 0;
};

// Interface for handling order events.
class IOrderEventsHandler {
public:
    virtual ~IOrderEventsHandler() = default;
    virtual void OnOrderEvent(const OrderEvent &event) = 0;
    virtual void OnReject(const OrderEvent &event) = 0;
    virtual void OnSendFailed(const std::string &status) = 0;
};

// Dummy SDK API functions.
inline void Initialize() {
    std::cout << "SDK Initialized (dummy)" << std::endl;
}

inline void Shutdown() {
    std::cout << "SDK Shutdown (dummy)" << std::endl;
}

inline InstrumentPtr GetInstrument(uint64_t id) {
    auto inst = std::make_shared<Instrument>();
    inst->id = id;
    return inst;
}

inline OrderPtr CreateOrder(InstrumentPtr, IOrderEventsHandler* /*handler*/) {
    // Return a new dummy order.
    return std::make_shared<Order>();
}

inline uint64_t SubscribeFastAggregateDepth(InstrumentPtr, IMarketDataHandler* /*handler*/) {
    // Return a dummy subscription id.
    return 1;
}

inline void Unsubscribe(uint64_t subscription_id) {
    std::cout << "Unsubscribed subscription id " << subscription_id << std::endl;
}

inline void SubscribeOrderEvents(const std::vector<int>& /*account_ids*/,
                                 IOrderEventsHandler* /*handler*/,
                                 bool /*download_book*/,
                                 bool /*listen_to_unsolicited_events*/ = false) {
    std::cout << "Subscribed to order events (dummy)" << std::endl;
}

} // namespace hgng_sdk

// Dummy implementation of folly::RWTicketSpinLockT to support the usage of RWSpinLock.
namespace folly {
template <int BitWidth, bool FavorWriter>
class RWTicketSpinLockT {
public:
    class ReadHolder {
    public:
        explicit ReadHolder(RWTicketSpinLockT* lock) { (void)lock; }
        ~ReadHolder() = default;
    };

    class WriteHolder {
    public:
        explicit WriteHolder(RWTicketSpinLockT* lock) { (void)lock; }
        ~WriteHolder() = default;
    };
};
} // namespace folly

#endif // MAIN_H
