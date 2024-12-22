#include "employee.h"
#include<iostream>
std::vector<Employee*> Employee::EmployeePointerList; // Definition of the static member
int main(){
    Engineer E1("Rahul");
    Manager M1("Mohit");
    Director D1("Gedon");

   for (auto it : Employee::getEmployeePointerList()) {
        it->ProcessSalary();
    }

    return 0;
}