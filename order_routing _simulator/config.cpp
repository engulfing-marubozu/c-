#include "config.h"
Config* Config::instance = nullptr;
ors:: error_code Config :: load(std::string file){
    try{
        std::ifstream fileContnt(file);
        nlohmann::json parsedJson;
        fileContnt>>parsedJson;
        exchange = parsedJson["exchange"];
        std::cout<<"Exchange loaded : "<<exchange<<std::endl;
        return ors ::error_code::SUCCESS;
    }
    catch(std::exception& e){
        return ors:: error_code :: FAILURE;
    }
}

Config* Config :: getConfigInstance(){
    if(instance == nullptr){
        instance = new Config();
    }
    return instance;
}

// double loading can be disbled here

//         if (!exchange.empty()) {
        //     throw std::logic_error("Config is already initialized and cannot be modified!");
        // }