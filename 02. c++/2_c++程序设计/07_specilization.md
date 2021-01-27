

**模板特化**

泛化: 我要用的时候你再指定类型就行了

```cpp
template <typename T>
struct hash {};
```


特化: 只能用特化里写的那些类型，注意语法

```cpp
#include<iostream>
using namespace std;

namespace test
{
    // 泛化
    template <typename T>
    struct hash {};

    // 特化 begin
    template < >
    struct hash<int> {
        int operator() (int x) const { return x; }
    };

    template < >
    struct hash<char> {
        char operator() (char x) const { return x; }
    };

    template < >
    struct hash<long> {
        long operator() (long x) const { return x; }
    };
    // 特化 end
}


int main(int argc, char const* argv[])
{
    cout << test::hash<int>()(1000) << endl;
    cout << test::hash<char>()('2') << endl;
    cout << test::hash<long>()(3000) << endl;
    return 0;
}
```

特化之前要写出泛化的版本.

**偏特化**

*情景一*

原来泛型的时候写成下面这样。

```cpp
template<typename T, typename Alloc = ...>
class vector
{
    ...
};
```

我有一种需求，我需要指定T为`bool`，而Alloc可以让使用者指定，那我就可以写成下面这样

```cpp
template<typename Alloc = ...>
class vector<bool, Alloc>
{
    ...
};
```

*情景二*

```cpp
// 部分1
template <typename T>
class C
{
public:
    void print() { cout << "T" << endl; }
};

// 部分2
template <typename T>
class C<T*>
{
public:
    void print() { cout << "T*" << endl; }
};

int main(int argc, char const *argv[])
{
    C<int>().print();
    C<int*>().print();
    return 0;
}
```

我写了一个普通的泛型的`class C`, 一个偏特化的`class C<T*>`，意思是告诉编译器，普通的对象，你用`部分1`的代码，指针你就用`部分2`的代码。

