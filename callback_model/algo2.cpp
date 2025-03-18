#include "algo2.hpp"
#include <iostream>
#include <thread>
Algo2::Algo2(int instrument) : _instrument(instrument) {}

void Algo2::OnPriceUpdate(const nlohmann::json& jsonData) {
    std::cout << "Algo 2" << std::hash<std::thread::id>{}(std::this_thread::get_id())<< " is running on Core " << sched_getcpu()  << std::endl;
}

void Algo2::start(ng_sdk& sdk_api) {
    sdk_api.Subscribe(_instrument, this);
}
