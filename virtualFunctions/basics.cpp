#include <iostream>
using namespace std;

class Animal {
public:
    virtual void sound() { // Virtual function
        cout << "Some generic animal sound" << endl;
    }
};

class Dog : public Animal {
public:
    void sound() override { // Override the base class function
        cout << "Bark" << endl;
    }
};

class Cat : public Animal {
public:
    void sound() override { // Override the base class function
        cout << "Meow" << endl;
    }
};

void makeSound(Animal* animal) { // Pointer to base class
    animal->sound(); // Calls the overridden sound() function
}

int main() {
    Dog dog;
    Cat cat;

    makeSound(&dog); // Output: Bark
    makeSound(&cat); // Output: Meow
    Animal *x;
    x = new Animal; // output "Some generic animal sound"
    x->sound();
    x= new Cat;
    x->sound(); // output Meow and not "Some generic animal sound"
    return 0;
}
