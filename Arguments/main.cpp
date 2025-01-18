#include<iostream>
using namespace std;

int main(int a, char **b){  // can write any variable name in place of a and b
    cout<<a<<endl;   // gives count of arguments
    cout<<b[0]<<endl; // gives the name of the file
    cout<<b[1]<<endl;  // gives the first argument
    return 0;
}


// input 
//  .\main.exe  78 89  56 6456

// Output
//  5
// C:\Users\rahul.raj\oop\Arguments\main.exe
// 78