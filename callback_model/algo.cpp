#include "algo.hpp"
#include <iostream>
#include <thread>
#include <sched.h>  // For sched_getcpu()
Algo::Algo(int instrument) : _instrument(instrument) {}

void Algo::OnPriceUpdate(PriceUpdate priceUpdate) {
    std::cout << "Algo 1 " << std::hash<std::thread::id>{}(std::this_thread::get_id()) << " is running on Core " << sched_getcpu() << std::endl;
}

void Algo::start(ng_sdk& sdk_api) {
    sdk_api.Subscribe(_instrument, this);
}
