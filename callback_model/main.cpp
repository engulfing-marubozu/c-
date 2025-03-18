#include <iostream>
#include "ng_sdk.hpp"
#include "algo.hpp"
#include "algo2.hpp"

int main() {
    ng_sdk sdk_api;
    Algo new_algo(1);
    new_algo.start(sdk_api);
    Algo2 new_algo2(2);
    new_algo2.start(sdk_api);
    sdk_api.Initialize();
    return 0;
}



