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
    Derived *derivedObj  = new Derived(); 
    Base* basePtr = dynamic_cast<Base*>(derivedObj); // Safe Upcasting and method overriding and runtime polymorphism
    basePtr->print(); 
    return 0;
}
