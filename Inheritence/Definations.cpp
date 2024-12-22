#include<iostream>
#include "inheritanceInterface.h"
using namespace inheritance;

void Base::display(){
    std::cout<<"test from the base class\n";
}

// void Derived::display(){
//     std::cout<<"test from the derived class\n";
// }

void Derived::display(std::string msg){
    std::cout<<"test from overloaded derived function "<<msg<<std::endl;
}

std::string Derived::getMessage(){
    return y;
}