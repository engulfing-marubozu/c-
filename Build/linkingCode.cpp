#include "pointers.h"
using namespace pointers;
TestPointerClass::TestPointerClass(ll age, std::string name) {
    this->age = age; 
    this->name = name;
}

void TestPointerClass::nameSetter(std::string name) {
    this->name = name;
}

void TestPointerClass::print() {
    std::cout << "values are \n" << name << " " << age<<std::endl;
}

// using namespace does not work for function definations
void pointers :: doNothing(){ 
    std::cout<<"doing nothing from pointer namespace\n";
}

void second :: doNothing(){ 
    std::cout<<"doing nothing from second namespace\n";
}
// perfect example of linking
// g++ -c asd.cpp -o asd.o  *to convert from cpp to object*
// this can be written seperately and compiled to object files


// g+++ asd.o as.o -o final.exe  * to finally link all the object files and convert to executables.*


// -c flag is for compiling from cpp to object file
// if we dont write -c flag, we can keep .cpp and object file both on the LHS, in RHS we alsways get exe.

// in 2 steps
//  g++ -c asd.cpp -o asd.o
// g++ asd.o -o asd.exe 

// in 1 step
// g++ asd.cpp -o asd.exe 