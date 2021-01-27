

### noexcept

```cpp
void foo() noexcept;
```

在函数的后面加上`noexcept`, 我保证这个函数不会丢出异常

其实`noexcept` 可以加上 `(condition expression)`

```cpp
void swap(Type&x, Type& y) noexcept( noexcept(x.swap(y)) )
{
    x.swap(y);
}
```

`swap` 保证不丢异常, 前提是 `x.swap(y)`不丢异常


**实际应用**

```cpp
class MyString
{
public:
    // move constructor
    MyString(MyString&& str) noexcept : _data(str._data), _len(str._len) {...}

    // move assignment
    MyString& opeartor=(MyString&& str) noexcept { ... return *this; }
private:
    char* _data;
    size_t _len;
    ...
};
```

当容器内空间不够, 发生`move`行为时, 如果类中的 `move`函数没有加`noexcept`, 容器则不会使用它.


### override

```cpp
class Base
{
    virtual void func(float) {}
};

struct Derived1: Base {
    virtual void func(int) {}
};
```

本意是要子类`override` 父类的func, 但是参数类型写错了, 子类自己定义了一个 `func(int)`函数;

```cpp
class Base
{
    virtual void func(float) {}
};

struct Derived1: Base {
    virtual void func(int) override {}
};
```

`virtual void func(int) override {}` 我在函数的后面加上`override` 主动告诉编译器我要覆盖, 编译器会自动帮我看参数类型是否错误.



### final

**修饰类**

```cpp
struct Base1 final {};

struct Derived1 : Base1 {}  // Error
```

类名后面加上 `final`, 告诉编译器, 我是继承体系下的最后一个, 不要再有其他的类继承我.



**修饰虚函数**

```cpp
struct Base2 {
    virtual void f() final;
};

struct Derived2 : Base2 {
    void f();
    // Error
};
```

虚函数后面加 `final` 告诉编译器, 这个虚函数不可以被`override`

