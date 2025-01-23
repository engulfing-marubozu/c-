#include<iostream>
#include "config.h"
#include "orsEngine.h"
#include<memory>
int main(int argc, char* argv[]){
    if(argc < 2){
        std::cout<<"No sufficient arguments!!"<<std::endl;
        return 0;
    }
    std::string config_file = argv[1];
    Config *cfg = Config::getConfigInstance();
    
    ors::error_code ret = cfg->load(config_file);
    if(ret == ors::FAILURE)
    {
        std::cout<<ors::getErrorCodeDescription(ret)<<std::endl;
        return 0;
    }   
    std:: unique_ptr<orsEngine> engine = std::make_unique<orsEngine>();
    ret = engine->Init(cfg); 
        if(ret == ors::FAILURE)
    {
        std::cout<<ors::getErrorCodeDescription(ret)<<std::endl;\
        std::cout<<"engine initialization failed. Shutting down!!"<<std::endl;
        return 0;
    } 

    std::string action;
    while(true){
        std::cout<<"Enter the action to perform "<<std::endl;
        std :: cin>>action;
        if (action == "N") {
            engine->sendOrder();
        } else if (action == "C") {
            engine->cancelOrder();
        } else if (action == "M") {
            engine->modifyOrder();
        } else if (action == "O") {
            engine->getOrderStatus();
        } else if (action == "T") {
            engine->getTradeStatus();
        } else {
           std::cout<<"Closing order simulator!!"<<std::endl;
           break;
        }
    }
    return 0;
}