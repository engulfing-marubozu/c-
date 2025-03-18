#include<iostream>
#include "sdk/sdk_api.h"
using namespace hgng_sdk;

int main(){

    Initialize();
    
    std::cout<<"Initialized"<<std::endl;  // flushing is important before the program ends.
    return 0;

}