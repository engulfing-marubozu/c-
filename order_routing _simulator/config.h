#pragma once

#include<istream>
#include<fstream>
#include "json.hpp"
#include "error_code.h"


class Config
{  
    Config() = default;
   public:
    static Config* instance;
    static Config* getConfigInstance();
    ors:: error_code load (std::string file);
    std::string exchange;
};





