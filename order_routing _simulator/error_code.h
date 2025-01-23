#pragma once

#include<iostream>

namespace ors{
enum error_code{
    SUCCESS,
    FAILURE
};

inline std::string getErrorCodeDescription(error_code code){
    switch(code){
        case SUCCESS:
            return "SUCCESS loading the config file";
        case FAILURE:
            return "FAILURE loading the config file";
        default:
            return "UNKNOWN";
    }
}
}

// should write different error codes for different failures like     ok,
    // failed_to_initalize,
    // failed_to_initalize_logger,
    // failed_to_load_config,


