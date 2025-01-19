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
    Base* basePtr = new Base();
    // Unsafe Downcasting
    try{
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr); // Unsafe: basePtr does not point to a Derived 
    if(derivedPtr == nullptr) {
        cout << "Downcasting failed" << endl;
    }else{
    derivedPtr->print(); // Undefined behavior
    derivedPtr->specific(); // Undefined behavior (likely crash)
    std::cout<<derivedPtr->specificValue; // Undefined behavior (likely crash)
    }
    }
    catch(std::exception &e){
      std::cout<<e.what()<<"hello all ";
    }
    return 0;
}
