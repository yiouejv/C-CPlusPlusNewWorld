

**模板模板参数**

```cpp
#include<iostream>
#include<list>
using namespace std;

template<typename T, 
                    template<typename T>
                        class Container
>
class XCls
{
private:
    Container<T> c;
};

int main(int argc, char const *argv[])
{
    // XCls<string, list> lst1; 语法不能通过
    return 0;
}
```

`XCls` 本身是一个模板，XCls的参数是一个模板。

`XCls<string, list> lst1;` 根据语法来说，XCls中的`T`为string，第二个模板参数`Container` 为 `list`, `Container<T>` 相当于 `list<string>`, 理论上应该能编译过。

但是实际上list还有其他的模板参数没有满足，编译不过。


下面这样就能过了，补上了list的第二个模板参数。

```cpp
#include<iostream>
#include<list>
using namespace std;

template<typename T,
                    template<typename U>
                        class Container
>
class XCls
{
private:
    Container<T> c;
};

template<typename T>
using Lst = list<T, allocator<T>>;

int main(int argc, char const* argv[])
{
    XCls<string, Lst> lst1;
    return 0;
}
```

重点: T 和 U 是可以不一样的，正如

```cpp
template<typename T>
using Lst = list<T, allocator<T>>;
```
是一个独立的模板。

-----------------

**这是不是模板模板参数？**

```cpp
template<typename T, class Sequence = deque<T>>
class stack
{
    friend bool operator== <> (const stack&, const stack&);
    friend bool operator< <> (const stack&, const stack&);
protected:
    Sequence c; // 底层容器
};

stack<int> s1;  // 可以通过
stack<int, list<int>> s2;  // 可以通过
```

虽然`template<typename T, class Sequence = deque<T>>` 第二个参数也是一个模板，但不是模板模板参数，因为，`deque<T>` 的T和第一个参数的T一定是保持一致的。
