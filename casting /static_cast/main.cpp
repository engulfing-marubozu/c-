#include<iostream>

// implicit conversion 
// explicit conversion
class Base{
  public :
 void print(std::string s){
    std::cout<<"Base class print function\n"<<s;
  }
};

class DerivedOne : public Base{
  public:
    int value = 20;
    void print() {
      std::cout<<"DerivedOne class print function\n";
    }

};

class DerivedTwo : public Base{
  public:
    int value = 30;
};


int main(){ 
    double a = 10.5;
    int b = a; // implicit conversion
    int c = static_cast<int>(a); // explicit conversion using static_cast
    int d = (int)a; // explicit conversion using C-style cast
    double e = (int)a + 10.5; // explicit conversion using C-style cast
    double f = static_cast<int>(a) + 10.5; // explicit conversion using static_cast

    Base *b1 = new DerivedOne();  
    try{
    std::cout<<static_cast<DerivedOne*>(b1)<<std::endl; // explicit conversion using static_cast
    DerivedOne *d1 =  static_cast<DerivedOne*>(b1); // explicit conversion using static_cast
    DerivedTwo *d2 =  (DerivedTwo*)b1; // c-style cast
    d1-> print();   // method hiding and not method overriding
    std::cout<<d1->value<<std::endl;
    d2->print("hello all");
    }
    catch(std::exception &e){
      std::cout<<e.what();
    }
    return 0;
}
