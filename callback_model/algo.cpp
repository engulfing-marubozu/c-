#include "algo.hpp"
#include <iostream>
#include <thread>
#include <sched.h>  // For sched_getcpu()
Algo::Algo(long long int instrument) : _instrument(instrument) {}

void Algo::OnPriceUpdate(PriceUpdate priceUpdate) {
    std::cout << "Algo 1 receive dupdate on" << std::hash<std::thread::id>{}(std::this_thread::get_id())<< " and core " << sched_getcpu()  << std::endl;
}

void Algo::start(ng_sdk& sdk_api) {
    sdk_api.Subscribe(_instrument, this);
}
