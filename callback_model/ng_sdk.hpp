#pragma once
#include <string>
#include <curl/curl.h>
#include <unordered_map>
#include <vector>
#include<thread>
#include "./json.hpp"

class IMarketDataHandler {
public:
    virtual void OnPriceUpdate(PriceUpdate PriceUpdate) = 0;
};

class PriceUpdate{
    public:
    std:: string instrument_name;
    int instrument_id;
    int bid;
    int ask;
    friend std::ostream& operator<<(std::ostream& os, const PriceUpdate& p) {
        os << "Instrument: " << p.instrument_name 
           << ", ID: " << p.instrument_id 
           << ", Bid: " << p.bid 
           << ", Ask: " << p.ask;
        return os;
    }
};
class ng_sdk {
public:
    void Initialize();
    void Subscribe(int instrument, IMarketDataHandler* subscriber);
    void publish(PriceUpdate PriceUpdate);
    void handleOrderUpdate(PriceUpdate PriceUpdate);
private:
    int cnt = 0;
    std::unordered_map<int, std::vector<IMarketDataHandler*>> instrument_subscribers_list;
    std::vector<std::thread*> threadPool;
};
