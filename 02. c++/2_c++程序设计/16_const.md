

**情景1: 放在成员函数后面，修饰函数**

```cpp
class Complex
{
public:
    double real() const {return re;}
    double imag() const {return im;}
private:
    double re, im;
};
```

普通的函数是不能放的，只能放类的成员函数。

作用是告诉编译器，我这个成员函数不打算改变`class member data`

加了`const`, 我保证不改变data，没加`const` 我不保证data不变。

```cpp
#include<iostream>
#include<string>
using namespace std;

class String : public string
{
    void print() { }
};

int main(int argc, char const *argv[])
{
    const String str("hello world");
    str.print();
    return 0;
}
```

`const String str` const 对象调用 non-const member function 会出错。

不是我的本意，我的本意是const对象肯定不会改变对象数据的，但是你却告诉我，调用`print`不保证数据不变，编译不过。

`void print() const {}` 加上 const 则没问题。

-------------------------------------------------
**实际应用**

```cpp
class template: std::basic_string< ... >
// 有如下两个member function

CharT
operator[] (size_type pos) const
{ ...  不必考虑 COW}

reference
operator[] (size_type pos)
{ ...  必须考虑 COW}
```

COW: Copy On Write

如果我是常量字符串`const string s;` 则我根本不需要考虑 COW, 直接调用带`const`的函数。

当成员函数的`const`和`non-const` 版本同时存在, `const object` 只会调用`const`版本，`non-const object`只会调用 `non-const` 版本。