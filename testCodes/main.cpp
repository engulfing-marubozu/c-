#include <iostream>
#include <memory> // For std::shared_ptr

class MainObject; // Forward declaration removed

class MainObject {
public:
    MainObject(int id) : id_(id) {}

    void createDependent();

    friend class Dependent;

private:
    int id_; // Main object's ID
};

class Dependent {
public:
    Dependent(MainObject obj) : id_(obj.id_) {}

    void show() {
        std::cout << "Dependent object ID: " << id_ << std::endl;
    }

private:
    int id_;
};

void MainObject::createDependent() {
    Dependent dependent(*this); // Using the current object's ID
    dependent.show();
}

int main() {
    MainObject* obj = new MainObject(42); // Create a main object with ID 42
    obj->createDependent();              // Create a dependent object using *this
    delete obj;                          // Clean up memory
    return 0;
}
