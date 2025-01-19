#include<iostream>
namespace ns{
    int x = 10;
    std::string y = "Hello";

    void display(){
        std::cout << "x: " << x << std::endl;
        std::cout << "y: " << y << std::endl;
    }
}