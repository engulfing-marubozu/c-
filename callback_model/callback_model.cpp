#include <iostream>
#include "ng_sdk.hpp"
#include "algo.hpp"
#include "algo2.hpp"
#include <random>
#include <csignal>
#include "KillSwitch.hpp"


void signalHandler(int signum) {
    if (signum == SIGINT) {
        std::cout << "\nCtrl+C detected! Stopping...\n";
        KillSwitch::getInstance().stop();
    }
}

int main() {
    signal(SIGINT, signalHandler);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3);
    {
        ng_sdk sdk_api(3);
        Algo new_algo(1561561651841161);
        new_algo.start(sdk_api);
        Algo2 new_algo2(6553865411133345);
        long long int instr_ids[] = {1561561651841161, 521114844444444, 6553865411133345, 465456346874343446};
        std::string instr_names[] = {"SR3_Dec24", "SO3_Dec24", "KE_Dec25", "ZW-Dec25"};
        float bid_base = 95;
        float ask_base = 95;
        new_algo2.start(sdk_api);
        for (long long int i = 0; i < 1000000000 ; i++) {
            if(KillSwitch::getInstance().isStopped()){
                std::cout<<"killing main loop\n";
                break;
            }
            int index = dist(gen);
            sdk_api.priceEvent(instr_ids[index], instr_names[index], (bid_base - 0.1 * index * 1.0), (bid_base + 0.1 * index * 1.0));
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        while (!KillSwitch::getInstance().isStopped()) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    } // Ensure sdk_api is destroyed here
    return 0;
}



