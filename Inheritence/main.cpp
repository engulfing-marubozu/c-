#include "inheritanceInterface.h"

using namespace inheritance;

int main(){
   Base base;
   base.display();
   Derived derived;
   derived.display(); 
   derived.display("hey I am overlaoded message");
   std::cout<<derived.show(); // accessing base class data members using get set 
   std::cout<<derived.getMessage(); // accessing base class data members using protacted members
   return 0;
}