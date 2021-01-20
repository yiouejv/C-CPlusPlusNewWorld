
1. 指针变量指向 变量的地址，引用变量代表了 一个变量。
2. 引用变量声明一定要初始化，因为引用变量的代表关系不能改变。

```c
#include<iostream>
using namespace std;


int main(int argc, char const* argv[])
{
    int x = 0;
    int* p = &x;
    int& r = x;

    int x2 = 5;
    r = x2;  // r代表了x, 所以相当于x = x2;
    return 0;
}
```

`int`的大小为4个字节，指针的大小在32位机器也是4个字节，引用的大小和代表的那个变量的类型大小保持一致。

注意: `sizeof(r) == sizeof(x)`, `&x == &r`, 编译器表现出来的是这样，实际上引用的内部实现是一个指针。

-------------------------------------------------------------
**reference 常见用途**

```cpp
void func1(Cls* pobj) { pobj->xxx(); }
void func2(Cls obj) { obj.xxx(); }
void func3(Cls& obj) { obj.xxx(); }

//...
Cls obj;
func1(&obj);  // 接口不同，困扰
func2(obj);
func3(obj);
```

`func2`, `func3`被调用端写法相同，很好，调用端写法相同，很好。

**reference 通常不用于声明变量，而用于参数类型和返回类型的描述**

-------------------------------------------------------------

```cpp
double imag(const double& img);
double imag(const double img);
```

这两行能不能同时存在？

不能，这两行的签名被视为相同的，same signature。

签名包括从函数名到 `{`中间的部分，不包含返回值的部分，函数返回值不同，签名相同，c++都认为是同一个函数，无法区分。

包括 `()` 和 `{}` 之间的`const`吗？

显然也包括。 

```cpp
double imag(const double& img) const {}
double imag(const double img) {}
```

以上两个函数会被认为是不同的函数。
