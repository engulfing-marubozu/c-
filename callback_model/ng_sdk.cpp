#include "ng_sdk.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

void ng_sdk::Initialize() {
     std::cout<<"SDK Initialized!!";
     for(int i=0; i<5 ;i++){
        threadPool.emplace_back(new std::thread);
     }
}

void ng_sdk::Subscribe(int instrument, IMarketDataHandler* subscriber) {
    std::cout << "Subscribed instrument " << instrument << std::endl;
    instrument_subscribers_list[instrument].push_back(subscriber);
}
void ng_sdk::handleOrderUpdate(PriceUpdate priceUpdate){
    std::cout<<priceUpdate;
    
}
void ng_sdk::publish(PriceUpdate priceUpdate) {
    std::cout << instrument_subscribers_list.size();
    for (auto& pair : instrument_subscribers_list) {
        if (cnt % pair.first == 0) {
            std::cout << "publishing to Algo " << pair.first << std::endl;
            for (auto& subscriber : pair.second) {
                subscriber->OnPriceUpdate(priceUpdate);
            }
        }
    }
}
