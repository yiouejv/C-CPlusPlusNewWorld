


### 字节对齐


1. 结构体变量的首地址能够被其最宽基本类型成员的大小所整除；

备注：编译器在给结构体开辟空间时，首先找到结构体中最宽的基本数据类型，然后寻找内存地址能被该基本数据类型所整除的位置，作为结构体的首地址。将这个最宽的基本数据类型的大小作为上面介绍的对齐模数。

2. 结构体每个成员相对于结构体首地址的偏移量（offset）都是成员大小的整数倍，如有需要编译器会在成员之间加上填充字节（internal adding）；

备注:为结构体的一个成员开辟空间之前，编译器首先检查预开辟空间的首地址相对于结构体首地址的偏移是否是本成员的整数倍，若是，则存放本成员，反之，则在本成员和上一个成员之间填充一定的字节，以达到整数倍的要求，也就是将预开辟空间的首地址后移几个字节。

3. 结构体的总大小为结构体最宽基本类型成员大小的整数倍，如有需要，编译器会在最末一个成员之后加上填充字节（trailing padding）。

```cpp
class A { int a = 1; short b = 1; int c = 1; char d = 'A'; };  // 16
class B { double a = 1; short b = 1; int c = 1; char d = 'A'; };  // 24
```


### 数组初始化

1. 未初始化的全局数组为0；
2. 未初始化的局部数组为随机值；
3. 初始化部分的全局数组与局部数组，初始化部分为初始化值，未初始化部分都为0；（不管全局还是局部）

### 逗号表达式

`int a,b;b=(a=3*5,a*4,a*5); printf("%d",b);`

逗号表达式是将括号中所有表达式的值算出来，但是只使用最后一个表达式。


### 构造函数初始化列表

```cpp
// 下面的程序输出可能是什么?
class Printer{
    public:
        Printer(std::string name) {std::cout << name;}
};
class Container{
    public:
        Container() : b("b"), a("a") {}
    Printer a;
    Printer b;
};
int main(){
    Container c;
    return 0;
}
```

初始化列表要注意，这道题故意写成b("b"), a("a") ，其实还是按类中声明变量的先后顺序来初始化，与初始化列表的顺序无关。


### 数组指针, 指针数组

```cpp
int a = 1, b = 2;
int arr[2]{1, 2};
int* p[2] = {&a, &b};
int(*q)[2] = &arr;
```


### 以下代码的输出结果是什么？

```cpp
int main(int argc, const char* argv[])
{
    int x = 2, y, z;
    x *= (y=z=5); cout << x << endl;
    z = 3;
    x == (y=z); cout << x << endl;
    x = (y == z); cout << x << endl;
    x = (y & z); cout << x << endl;
    y = 4;
    x = (y | z); cout << x << endl;
    x = (y || z); cout << x << endl;
    return 0;
}
```

```cpp
int main(int argc, const char* argv[])
{
    int x = 2, y, z;
    x *= (y=z=5); cout << x << endl;  // x = x * y;  x = 2 * 5;  10
    z = 3;
    x == (y=z); cout << x << endl;  // x == y; x 没变， x = 10;
    x = (y == z); cout << x << endl;  // y == z; 为真，x = 1;
    x = (y & z); cout << x << endl;  // x = (3 按位与 3); x = 3;
    x = (y && z); cout << x << endl;  // x = (3 与 3); x = 1;
    y = 4;
    x = (y | z); cout << x << endl;  // x = (4 按位或 3); x = 7;
    x = (y || z); cout << x << endl;  // x = (4 或 3); x = 1;
    return 0;
}
```

### 以下代码的输出结果是什么？

```cpp
int func(int x)
{
    int count = 0;
    while (x) {
        ++count;
        x = x & (x - 1);
    }
    return count;
}


int main(int argc, const char* argv[])
{
    cout << func(9999) << endl;
    return 0;
}

```


### 以下代码的输出结果是什么？

```cpp
#include<cstdio>

int main(int argc, const char* argv[])
{
    int b = 3;
    int arr[] = {6,7,8,9,10};
    int* ptr = arr;
    *(ptr++) += 123;
    printf("%d %d\n", *ptr, *(++ptr));
    return 0;
}
```


```cpp
#include<cstdio>

int main(int argc, const char* argv[])
{
    int b = 3;
    int arr[] = {6,7,8,9,10};
    int* ptr = arr;  // ptr 指向6的地址
    *(ptr++) += 123;  // 等价于 *ptr += 123; ptr++; arr的值为 {129，7，8，9，10}，ptr指向7
    printf("%d %d\n", *ptr, *(++ptr));  // printf从右往左压栈，++ptr, ptr 指向8的位置，输出 8 8
    return 0;
}
```

### 以下代码的输出结果是什么？

```cpp
#include<cstdio>


int main(int argc, const char* argv[])
{
    unsigned int a = 0xFFFFFFF7;
    unsigned char i = (unsigned char) a;
    char* p = (char*)&a;
    printf("%08x %08x", i, *p);
    return 0;
}
```

在x86系列的cpu中，使用的是小端模式，低地址放数据的地位，F7放在第一个字节的位置，所以`unsigned int a = 0x000000F7`, p 指向 a的地址，由于 p是有符号char类型，所以`*p`的值为0xFFFFFFF7,
内存里存放的是数据的补码。 所以输出： 000000F7, fffffff7


