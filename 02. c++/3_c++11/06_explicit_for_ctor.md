


C++2.0 之前 `explicit` 用在一个实参的 ctor上。

参考: <a href="../2_c++程序设计/02_non_explicit_one_argument_ctor.md">2_c++程序设计/02_non_explicit_one_argument_ctor.md</a>

----------------------------------------

explicit for ctors taking more than one argument

2.0 以后 `explicit` 可以用在 包含多个参数的构造函数上.

```cpp
class P
{
public:
    P(int a, int b) { cout << "P(int a, int b)" << endl; }
    P(initializer_list<int> initList) { cout << "initializer_list<int> initList" << endl; }
    explicit P(int a, int b, int c) { cout << "explicit P(int a, int b, int c)" << endl; }
};

P p1 (77, 5);       // P(int a, int b)
P p2 {77, 5};       // initializer_list<int> initList
P p3 {77, 5, 42};   // ERROR
P p4 = {77, 5};     // initializer_list<int> initList
P p5 = {77, 5, 43};   // ERROR
P p6 (77, 6, 3);    // explicit P(int a, int b, int c)
```






