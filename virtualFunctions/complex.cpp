#include <iostream>
using namespace std;

class A {
public:
    // Virtual functions to support polymorphism
    virtual void f(int) {
        cout << "A::f(int) called\n";
    }

    virtual void g(double) {
        cout << "A::g(double) called\n";
    }

    int h(A*) {
        cout << "A::h(A*) called\n";
        return 0;
    }
};

class B : public A {
public:
    // Override f() in B (non-virtual here but it overrides A's implementation)
    void f(int) override {
        cout << "B::f(int) called\n";
    }

    // Override h() in B (virtual) for B* argument
    virtual int h(B*) {
        cout << "B::h(B*) called\n";
        return 0;
    }
};

class C : public B {
public:
    // Override g() in C
    void g(double) override {
        cout << "C::g(double) called\n";
    }

    // Override h() in C (virtual) for B* argument
    int h(B*) override {
        cout << "C::h(B*) called\n";
        return 0;
    }
};

int main() {
    A a;
    B b;
    C c;

    // Pointers of type A* and B* to test polymorphism
    A *pA;
    B *pB;

    // Testing all cases with pA
    pA = &a;
    pA->f(2);           // A::f(int)
    pA->g(3.2);         // A::g(double)
    pA->h(&a);          // A::h(A*)
    pA->h(&b);          // A::h(A*)

    cout << "-----------------\n";

    pA = &b;
    pA->f(2);           // B::f(int)
    pA->g(3.2);         // A::g(double) (since B does not override g)
    pA->h(&a);          // A::h(A*)
    pA->h(&b);          // B::h(B*)

    cout << "-----------------\n";

    pA = &c;
    pA->f(2);           // B::f(int)
    pA->g(3.2);         // C::g(double)
    pA->h(&a);          // A::h(A*)
    pA->h(&b);          // C::h(B*)

    cout << "-----------------\n";

    // Now testing with pB
    pB = &b;
    pB->f(2);           // B::f(int)
    pB->g(3.2);         // A::g(double) (since B does not override g)
    pB->h(&b);          // B::h(B*)

    cout << "-----------------\n";

    pB = &c;
    pB->f(2);           // B::f(int)
    pB->g(3.2);         // C::g(double)
    pB->h(&b);          // C::h(B*)
    pB->h(&c);     // This will call A::h(A*) since it's casted to B*

    return 0;
}
