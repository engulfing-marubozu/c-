#include <iostream>
class B;
class A
{
    int a;

public:
    void add(B y);
    A(int x) : a(x) {};
};

class B
{
    int b;

public:
    B(int x) : b(x) {};
    friend void A::add(B y);
};

void A::add(B y)
{
    std::cout << this->a + y.b << std::endl;
}

int main()
{
    A m(4);
    B n(5);
    m.add(n);
    return 0;
}

// 📌 Make the function a member of one class &a friend of the other class.
// 📌 This avoids inheritance but still allows private member access of both the class.
