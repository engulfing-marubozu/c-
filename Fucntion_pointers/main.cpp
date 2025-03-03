#include <iostream>

void sayHello(int a) { std::cout << "Hello!\n"; std::cout<<a<<std::endl; }
void sayGoodbye(int b) { std::cout << "Goodbye!\n"; std::cout<<b<<std::endl; }

int main() {
    // Declare an array of function pointers
    void (*funcArr[])(int) = { sayHello, sayGoodbye };

    funcArr[0](4);  // Calls sayHello()
    funcArr[1](5);  // Calls sayGoodbye()

    return 0;
}

//output:
// Hello!
// 4
// Goodbye!
// 5


// void (*ptr)()	ptr is a pointer to a function returning void.
// void (*funcArr[])()	funcArr is an array of function pointers, where each function returns void and takes no arguments.
// void (*funcArr[])(int)	funcArr is an array of function pointers, where each function takes an int argument and returns void.
