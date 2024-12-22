#ifndef POINTERS_H   
#define POINTERS_H

#include <iostream>
#include <string>

#define ll long long int
namespace pointers
{
    class TestPointerClass {
    ll age;
    std::string name;
public:
    TestPointerClass(ll age, std::string name);
    void nameSetter(std::string name);
    void print();
};

void doNothing();
} // namespace pointers

namespace second{
    void doNothing();
}

#endif // POINTERS_H
