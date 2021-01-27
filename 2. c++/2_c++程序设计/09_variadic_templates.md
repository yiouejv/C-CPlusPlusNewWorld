

Variadic template (Since C++ 11)

```cpp
#include<iostream>
using namespace std;

void print()
{

}

template <class T, class... types>
void print(const T& firstArg, const types&... args)
{
    cout << firstArg << endl;
    cout << "sizeof args" << sizeof...(args) << endl;
    print(args...);
}

int main(int argc, char const* argv[])
{
    print(1, "hello", 4.0);
    return 0;
}
```

可变的模板参数，`c++11` 之前的版本，模板参数是固定的，11之后引入了可变的模板参数，注意语法。

`print(1, "hello", 4.0);` 会调用上面的函数模板，`1`作为`firstArg`传入print，后面两个参数作为一个pack，放在args中，

```cpp
cout << firstArg << endl;
print(args...);
```

打印第一个参数，再把`args...`传入`print`，`"hello"` 变成了第一个参数，`4.0` 打包成`args`,

再调用`print`, `4.0` 变成第一个参数，`args...` 变为空，调用 `void print(){}` 函数，最后结束。



