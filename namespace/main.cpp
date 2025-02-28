#include<iostream>
#include "ns.cpp"
#include "nsExtend.cpp"
namespace ns{
    int xi = 20;
}
int main(){
    std::cout << "x: " <<ns:: xi << std::endl;
    std::cout << "y: " << ns:: yi << std::endl;  
    ns::display();
    return 0;
    printf("Hello World Rahul");
}