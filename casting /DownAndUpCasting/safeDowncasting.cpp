#include <iostream>
using namespace std;

class Base {
public:
    virtual void print() {
        cout << "Base class print function" << endl;
    }
};

class Derived : public Base {
public:
    int specificValue = 42;
    void print() override {
        cout << "Derived class print function" << endl;
    }
    void specific() {
        cout << "Derived class specific function" << endl;
    }
};

int main() {
    Base* basePtr = new Derived(); // upcasting
    try{
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr); // safe: basePtr point to a Derived
    if(derivedPtr == nullptr) {
        cout << "Downcasting failed" << endl;
    }else{
    derivedPtr->print(); 
    derivedPtr->specific(); 
    std::cout<<derivedPtr->specificValue; 
    }
    }
    catch(std::exception &e){
      std::cout<<e.what()<<"hello all ";
    }
    return 0;
}
