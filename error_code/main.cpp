#include <iostream>
#include <string>
#include "enums.h"

using namespace hgng_ns;
int main() {
   
    // Simulate an error
    error_code result = error_code::failed_to_initialize;
    
    // Print the error description
    std::cout << "Error: " << GetErrorDesc(result) << std::endl;
    std::cout << "Error: " << GetErrorDesc(error_code::ok) << std::endl;

    return 0;
}
