#ifndef POINTERS_H   
#define POINTERS_H

#include <iostream>
#include <string>
namespace inheritance
{
    class Base {
      std::string x ="private member\n";
      protected:
      std::string y ="protacted member\n";
      public:
       void display();
       std::string show(){
        return x;
       }
};

 class Derived : public Base{
    public:
    using Base::display;
  //   void display(); // override and not overload
     void display(std::string); // overlaoded 
     std::string getMessage();
 };
} // inheritance pointers


#endif // POINTERS_H
