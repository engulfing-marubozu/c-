#include<iostream>
#include<memory>
using namespace std;
class Base{
public:
  int x;
  Base(int x):x(x){}
};

class Derived: public Base{
    public:
  int y;
  Derived(int x):Base(x){};
};

int main(){
    Base *b = new Derived(10);
    shared_ptr<Base> d = make_shared<Derived>(10);
    cout<< d->x<<endl;
    return 0;
}