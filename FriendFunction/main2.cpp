#include <iostream>
class B;
class A
{
    int a;

public:
    friend void add(A x , B y);
    A(int x) : a(x) {};
};

class B
{
    int b;

public:
    B(int x) : b(x) {};
    friend void add(A x, B y);
};

void add(A x, B y)
{
    std::cout << x.a + y.b << std::endl;
}

int main()
{
    A m(4);
    B n(5);
    add(m,n);
    return 0;
}

// 📌 Make the function  friend of both the class.
// 📌 This avoids inheritance but still allows private member access of both the class.
