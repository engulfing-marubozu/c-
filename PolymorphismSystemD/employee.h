#include<iostream>
#include<vector>
class Employee{
    protected:
    std::string name_;
    static std:: vector<Employee*> EmployeePointerList;
    int salary;
    public:
    virtual void ProcessSalary()=0;
    static std::vector<Employee*> getEmployeePointerList(){return EmployeePointerList;};
};
// Abstract class

class  Engineer: public Employee{
    public:
   Engineer(std :: string name){name_ = name;
   EmployeePointerList.push_back(this);};
   void ProcessSalary() override{std::cout<<"Processing salary for Engineer "<<name_<<"\n";};
};

class Manager: public Engineer{
    public:
    Manager(std:: string name):Engineer(name){};
    void ProcessSalary() override{std::cout<<"Processing salary for Manager "<<name_<<"\n";};;
};

class Director: public Manager{ 
    public:
    Director(std::string name):Manager(name){};
    void ProcessSalary() override{std::cout<<"Processing salary for Director "<<name_<<"\n";};;
};


