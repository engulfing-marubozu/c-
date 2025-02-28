#include<iostream>


struct Helper{
    static void staticFunc(){
        std::cout << "Hello from static Helper" << std::endl;
    }
   void nonStaticFunc(){
        std::cout << "Hello from non static Helper" << std::endl;
    }
};