
**情景一： 设初值**

```cpp
int i;  // i has undefined value
int j{};  // j is intializad by 0
int* p;  // p has undefined value
int* q{};  // q is initialized by nullptr
```

**情景二: 转换的时候是不允许窄化的转换**

```cpp
int x1(5.3);
int x2{5.0};  // ERROR
char c1{7};
char c2{9999};  // ERROR
```


--------------------------------


```cpp
void print(std::initializer_list<int> vals)
{
    for (auto p = vals.begin(); p != vals.end();  ++p) {
        cout << *p << endl;
    }
}

print( {1, 2, 3, 4, 5, 6, 7} );  // pass a list of values to print()
```

------------------------------------------

```cpp
class A
{
public:
    A(int a, int b)
    {
        cout << "A(int, int), a=" << a << ", b=" << b << endl;
    }
    A(initializer_list<int> initList)
    {
        cout << "A(initializer_list<int>), values=";
        for (auto i : initList)
            cout << i << " ";
        cout << endl;
    }
};

A a(77, 5);
A b{77, 5};
A c{77, 5, 33};
A d = {77, 6};
```

----------------------------------------------------------

```cpp
#include<iostream>
using namespace std;


class A
{
public:
    A(int a, int b)
    {
        cout << "A(int, int), a=" << a << ", b=" << b << endl;
    }
    /*A(initializer_list<int> initList)
    {
        cout << "A(initializer_list<int>), values=";
        for (auto i : initList)
            cout << i << " ";
        cout << endl;
    }*/
};


int main(int argc, char const* argv[])
{
    A a(77, 5);;
    A b{ 77, 5 };
    // A c{ 77, 5, 33 }; 
    A d = { 77, 6 };
    return 0;
}
```

如果 `A(initializer_list<int> initList)` 版本不存在，编译器会把 `initializer_list` 拆成单个的参数传递给构造函数.

---------------------------------------------------------

