// 本示例演示 继承和复合下的构造函数，析构函数的调用先后顺序
#include <iostream>
using namespace std;


class A
{
public:
    A() { cout << "A ctor is run\n"; }
    ~A() { cout << "A dtor is run\n"; }
};


class B
{
public:
    B() { cout << "B ctor is run\n"; }
    ~B() { cout << "B dtor is run\n"; }
};


class C : public A
{
public:
    C() { cout << "C ctor is run\n"; }
    ~C() { cout << "C dtor is run\n"; }
private:
    B data;
};


int main(int argc, char const* argv[])
{
    C c; // A B C C B A
    return 0;
}