#include "algo2.hpp"
#include <iostream>
#include <thread>
Algo2::Algo2(long long int instrument) : _instrument(instrument) {}

void Algo2::OnPriceUpdate(PriceUpdate priceUpdate) {
    std::cout << "Algo 2 receive dupdate on" << std::hash<std::thread::id>{}(std::this_thread::get_id())<< " and core " << sched_getcpu()  << std::endl;
}

void Algo2::start(ng_sdk& sdk_api) {
    sdk_api.Subscribe(_instrument, this);
}
