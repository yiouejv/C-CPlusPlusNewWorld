
### new 先分配memory，再调用ctor

```cpp
Complex* pc = new Complex(1, 2);
```

编译器转化为

```cpp
Complex* pc;

void* mem = operator new( sizeof(Complex) );  // 分配内存，其内部调用的malloc(n)
pc = static_cast<Complex*>(mem);  // 类型转换
pc->Complex::Complex(1, 2);  // 构造函数
``` 

### delete 先调用dtor, 再释放memory

```cpp
String* ps = new String("hello");
...
delete ps;
```

编译器转化为

```cpp
ps->String::~String();  // 析构函数, 释放指针指向的内存块
operator delete(ps);  // 释放内存，其内部调用free(ps), 释放指针
```

------------------------------------
### 重载operator new, operator new[], operator delete, operator delete[]

*声明为全局的*

```cpp
void* myAlloc(size_t size)
{ return malloc(size); }

void myFree(void* ptr)
{ free(ptr); }


void* operator new(size_t size)
{ cout << "global new \n"; return myAlloc(size); }

void* operator new[](size_t size)
{ cout << "global new[] \n"; return myAlloc(size); }

void operator delete(void* ptr)
{ cout << "global delete \n"; myFree(ptr); }

void operator delete[](void* ptr)
{ cout << "globale delete[] \n"; myFree(ptr);}
```

全局的`operator new` ... 不可声明为`inline`函数。


*重载类的*

```cpp
#include <iostream>
using namespace std;

void* myAlloc(size_t size)
{ return malloc(size); }

void myFree(void* ptr)
{ free(ptr); }

class A
{
public:
    A(){}
    ~A(){}
    void* operator new(size_t size)
    { cout << "A override operator new \n"; return myAlloc(size);}

    void* operator new[](size_t size)
    { cout << "A override operator new[] \n"; return myAlloc(size);}

    void operator delete(void* ptr)
    { cout << "A override operator delete \n"; myFree(ptr); }

    void operator delete[](void* ptr)
    { cout << "A override operator delete[] \n"; myFree(ptr); }
};

int main(int argc, char const* argv[])
{
    A* a = new A;
    delete a;
    return 0;
}
```


--------------------------------------

**强制采用全局的operate new, delete**

```cpp
#include<iostream>
using namespace std;

void* myAlloc(size_t size)
{ return malloc(size); }

void myFree(void* ptr)
{ return free(ptr); }

void* operator new(size_t size)
{ cout << "global operator new \n"; return myAlloc(size); }

void operator delete(void* ptr)
{ cout << "global operator delete \n"; myFree(ptr); }

class A
{
public:
    void* operator new(size_t size)
    { cout << "A operator new \n"; myAlloc(size); }

    void operator delete(void* ptr)
    { cout << "A operator delete \n"; myFree(ptr); }
};

int main(int argc, char const *argv[])
{
    A *a = ::new A;
    ::delete a;
    return 0;
}
```

在 `new`，`delete` 前面加 `::`, 强制使用全局的 `operator new` `operator delete`


----------------------------------------------------

**placement new() delete()**

我们可以重载 class member operator new(), 写出多个版本，前提是每一个版本的声明都必须有独特的参数列，

其中第一个参数必须是`size_t`, 其余参数以 `new` 所指定的 `placement arguments` 为初值，出现于 `new(...)` 小括号内的便是所谓的`placement arguments`。

```cpp
class Bad
{};

class Foo
{
public:
    Foo() { cout << "Foo::Foo()" << endl; }
    Foo(int) { cout << "Foo::Foo(int)" << endl; throw Bad();}

    // (1) 这个就是一般的 operator new() 的重载
    void* operator new(size_t size) {
        return malloc(size);
    }

    // (2) 这个就是标准库已经提供的 placement new() 的重载形式
    void* operator new(size_t size, void* start) {
        return start;
    }

    // (3) 这个才是崭新的 placement new
    void* operator new(size_t size, long extra) {
        return malloc(size+extra);
    }

    // (4) 这又是一个 palcement new
    void* operator new(size_t size, long extra, char init) {
        return malloc(size+extra);
    }
};
```

我们也可以重载class member operator delete(), 写出多个版本，但他们绝不会被`delete`调用，只有当`new`所调用的`ctor`抛出`exception`, 才会调用这些重载版的 `operator delete()`。  


他们只可能这样被调用，主要用来归还未能**完全创建成功**的object所占用的memory。

即使`operator delete(...)` 未能一一对应 `operator new(...)`，也不会出现任何报错，你的意思是: 放弃处理ctor发出的异常。


------------------------------------------------------

标准库里实际应用了 `operator new` 的场景

```cpp
class basic_string
{
private:
    struct Rep{
        ... 

        void release() { if --ref == 0; delete this; }
        inline static void* operator new(size_t, size_t);
        inline static void operator delete(void*);
        inline static Rep* create(size_t);

        ...
    };
    ...
};

...
create (size_t extra)
{
    extra = frob_size(extra + 1);
    Rep *p =  new(extra) Rep;
    ...
    return p;
}

...
operator new(size_t s, size_t extra)
{
    return Allocator::allocate(s + extra * sizeof(charT));
}
```

`basic_string` 里有个引用计数，`extra` 才是保存字符串的空间，