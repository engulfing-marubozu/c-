#include "pointers.h"
// all the function declarations coming from pointer.h and definitions from linkingCode.cpp
using namespace pointers;
int main() {
    doNothing(); // imported by linking. needs to be linked through linker to execute this.
    second :: doNothing();
    TestPointerClass* ptr = new TestPointerClass(20, "Rahul");
    ptr->nameSetter("Rahul's new name");
    ptr->print();  // call like this 
    (*ptr).print();  // or like this
    delete ptr; // Don't forget to free allocated memory
    return 0;
}

// *** ALL THE DECLARATIONS IN 'pointer.h' i.e HEADER FILE and all the definations in 'linkingCode.h' i.e. COMMON DEFINITION FILE SO THAT THE DEFINITION GETS INCLUDED ONLY ONCE IN THE WHOLE CODEBASE AT THE TIME OF LINKING****
// AS WE HAVE ADDED DECLARATIONS IN HEADER FILES, SO COMILING THEM SEPRERATE INTO OBJECT FILES WON'T THROW ANY ERROR.
// CONVERT .cpp to .o seperately then link them through linker. 