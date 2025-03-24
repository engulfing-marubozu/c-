#include <string>
#pragma once
#include <curl/curl.h>
#include <queue>
#include <unordered_map>
#include <vector>
#include <thread>
#include <condition_variable>
#include "./json.hpp"
#include <memory>
#include "KillSwitch.hpp"

class ng_sdk;
class PriceUpdate {
    public:
    PriceUpdate(long long int instr_id , std::string instr_name , float bid_price, float ask_price): instrument_id(instr_id), instrument_name(instr_name), bid(bid_price), ask(ask_price){};
    std:: string instrument_name;
    long long int instrument_id;
    float bid;
    float ask;
    friend std::ostream& operator<<(std::ostream& os, const PriceUpdate& p) {
        os << "Instrument: " << p.instrument_name 
           << ", ID: " << p.instrument_id 
           << ", Bid: " << p.bid 
           << ", Ask: " << p.ask;
        return os;
    }
};

class IMarketDataHandler {
    public:
        virtual void OnPriceUpdate(PriceUpdate PriceUpdate) = 0;
};

class Threadpool {
    public:
        Threadpool(ng_sdk &ng_sdk, int num_threads);
        ~Threadpool();
        void pushPriceToStream(PriceUpdate priceUpdate);
    private:
        std::queue<PriceUpdate> priceStream;
        std::mutex m;
        std::condition_variable cv;
        std::vector<std::thread> threads;
        int _num_threads;
};

class ng_sdk {
public:
    ng_sdk(int poolSize);
    void Subscribe(long long int instrument, IMarketDataHandler* subscriber);
    void publish(PriceUpdate PriceUpdate);
    void handleOrderUpdate(PriceUpdate PriceUpdate);
    void priceEvent(long long int instr_id, std::string instr_name, float bid_price, float ask_price);
    bool hasSubscribers(long long int instrument);
private:
    int cnt = 0;
    std::unordered_map<long long int, std::vector<IMarketDataHandler*>> instrument_subscribers_list;
    std::unique_ptr<Threadpool> pool;
    std::mutex subscribers_mutex;
};
