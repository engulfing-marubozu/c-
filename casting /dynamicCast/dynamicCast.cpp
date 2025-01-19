#include<iostream>

class Base{
     // for dynamic cast we need to have at least one virtual function in the base class as it looks for the vtable to perform the downcasting
  public:
    virtual void print(std::string s){
      std::cout<<"Base class print function\n"<<s;
    }
};

class DerivedOne : public Base{
  public:
    int value = 20;
     void print(std::string s) override {
      std::cout<<"DerivedOne class print function\n"<<s;
     }
};

int main(){
  // example of safe downcasting using dynamic cast
    Base *b1 = new DerivedOne();
    DerivedOne *d1 = dynamic_cast<DerivedOne*>(b1); // explicit conversion using dynamic_cast
    std::cout<<d1->value<<std::endl;

 // example of unsafe downcasting using dynamic cast
     Base *b2 = new Base();
    DerivedOne *d2 = dynamic_cast<DerivedOne*>(b2); // explicit conversion using dynamic_cast
    if(d2 == nullptr){
      std::cout<<"Downcasting failed\n";
    }
    else
    std::cout<<d2->value<<std::endl;

       return 0;
}