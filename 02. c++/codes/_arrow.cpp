#include<iostream>
using namespace std;

class A
{
public:
    A(int n) : a(n) {}
    int a;
};


int main(int argc, char const *argv[])
{
    A* o = new A(2);
    cout << (*o).a << endl;
    cout << o->a << endl;
    // o.a;  报错
    // -> 等价于 解引用 , .
    return 0;
}