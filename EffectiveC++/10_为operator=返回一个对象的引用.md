
为 operator= 返回一个对象的引用

请遵守这个协议

看这个例子

```C++
#include<iostream>
using namespace std;

class A {
public:
    A() {}
    A(int a) : m_a(a) {}
    ~A() {}
    A& operator=(const A& a) {
        m_a = a.m_a;
        return *this;
    }
private:
    int m_a;
};

int main(int argc, char const *argv[])
{
    A a1(1);
    A a2;
    A a3;
    a3 = a2 = a1;
    return 0;
}
```

定义了一个类A

operator= 的定义遵守协议

假如执行赋值语句 a3 = a2 = a1

赋值采用右结合律

上述连锁赋值将被解析为

a3 = (a2 = a1)

先将对象a1拷贝给a2

再将其结果(也就是函数的返回值)拷贝给a3

为了实现连锁赋值

赋值操作符必须返回一个reference指向操作符的左侧实参

<img src="../images/09_01.png">

除了 operator= 以外

类似的赋值操作符也一样

operator+=

operator-=

`operator*=`

等等

这个协议不遵守也能编译过

但是C++的内置类型和标准库都遵守了

如果你没有好的理由还是和大家一样吧



