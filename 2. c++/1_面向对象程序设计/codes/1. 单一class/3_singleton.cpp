#include <iostream>
using namespace std;

class A
{
public:
    static A& getInstance();
private:
    A();
    A(const A& rhs);
};

inline
A::A()
{

}

inline
A::A(const A& rhs)
{

}

inline A&
A::getInstance()
{
    static A a;
    return a;
}


int main(int argc, char const* argv[])
{
    return 0;
}