

如果你自行定义了一个 `ctor`, 那么编译器就不会再给你一个 `default ctor`

如果你强制加上 `=default`, 就可以重新获得并使用 `default ctor`

编译器给你的默认的构造函数有什么用呢？

如果你是一个单一的类，没有继承关系，没什么用。 因为它什么都没做，如果你是一个子类，编译器给你的默认构造函数会帮你调用父类的构造函数。

```cpp
class Zoo
{
public:
    Zoo(int i1, int i2) : d1(i1), d2(i2) {}
    Zoo(const Zoo&) =delete;
    Zoo(Zoo&&) =default;
    Zoo& operator=(const Zoo&) =default;
    Zoo& operator=(const Zoo&&) =delete;
    virtual ~Zoo() {}
private:
    int d1, d2;
};
```

```cpp
class Foo
{
public:
    Foo(int i) : _i(i) {}
    Foo() = default;  // 于是和上一个并存 （ctor可以多个并存）

    Foo(const Foo& x) : _i(x._i) {}
    //! Foo(const Foo&) = default;  // [Error] Foo:Foo(const Foo&) cannot be overload
    //! Foo(const Foo&) = delete;  // [Error] Foo:Foo(const Foo&) cannot be overload

    Foo& operator=(const Foo& x) { _i = x._i; return *this; }
    //! Foo& operator=(const Foo& x) = default // [Error] Foo& Foo::operator=(const Foo&) cannot be overload
    //! Foo& operator=(const Foo& x) = delete // [Error] Foo& Foo::operator=(const Foo&) cannot be overload

    //! void func1() = default // [Error] void Foo::func1() cannot be defaulted
    void func2() = delete;  // ok

    //! ~Foo() = delete  // 这会造成使用Foo object 时出错 ==> [Error] use of deleted function Foo::~Foo()
    ~Foo() = default;
private:
    int _i;
};

Foo f1(5);
Foo f2;  // 如果没有写出 Foo() = default 的版本则无法匹配到构造函数
Foo f3(f1);  // 如果 copt ctor = delete，[Error]use of deleted function
f3 = f2;  // 如果 copy assign = delete. [Error]use if deleted function
```

`=delete` 告诉编译器，这个函数我不想要，如果代码里引用了这个函数，则编译不过。 可以用于任何函数身上。

`=default` 用于 *构造函数*，*拷贝构造*，*拷贝赋值*，*右值拷贝*，*右值赋值*，*析构函数* 之外的普通函数，有意义吗？  没有意义

`=0` 只能用于 `virtual` 函数


---------------------------------------------------

**什么时候 empty class 不再是 empty 呢？**

当 c++ 处理过之后，是的，如果你自己没声明，编译器就会为它声明一个 `copy ctor`，一个 `copy assignment operator` 和一个 `dtor`, 如果你没有声明任何`ctor`, 编译器会为你声明一个default ctor。 所有这些函数都是 `public` 且 `inline`

```cpp
class Empty {};
```

惟有当这些函数被调用，他们才会被编译器生成，以下造成每个函数被编译器生成。

```cpp
{
    Empty e1;  // 编译器会生成 Empty() {...}
    Empty e2(e1);  // 编译器会生成 Empty(const Empty& rhs) {...}
    e2 = e1;  // 编译器会生成 Empty& operator=(const Empty& rhs) { ... }
}  // 编译器生成 ~Empty() {...}
```

```cpp
class Empty
{
public:
    Empty() { ... }
    Empty(const Empty& rhs) { ... }
    Empty& operator=(const Empty& rhs) { ... }
    ~Empty() {}
};
```

这些函数有什么用呢？

如果是单一的函数，用处不是很大，`default ctor` `default dtor` 主要是给编译器一个地方用来放置幕后的code，像是唤起 `base class` 以及 `non-static members` 的 `ctors`, `dtors`

编译器产生的 `dtor` 是 `non-virtual`，除非这个`base class` 本身有宣告 `virtual dtor`。

至于 `copy ctor` `copy assignment operator`, 编译器合成版只是单纯将 `source object` 的每一个 `non-static data member` 拷贝到 destination object

-----------------------------------------------------

**什么时候需要主动写出来？**

如果类内不包含指针成员，用编译器默认提供的这些就基本上够用了。

如果类内包含指针成员，则需要我们自己去定义。


不包含指针成员的类，拷贝赋值单纯的将原数据拷贝到目标对象，编译器提供的默认的就是做这个事情的，够用。

但是包含指针成员的类，拷贝分为浅拷贝和深拷贝，编译器提供的默认的拷贝赋值 拷贝的只是指针对象，属于浅拷贝，两个指针指向同一块内存空间; 深拷贝则是需要把指针指向的那一块内存也拷贝到目的对象，需要自己实现。

-----------------------------------------------------------

**=default, =delete 应用** 

1. 如果你设计一个类不允许别人来拷贝它，你可以这么写

```cpp
struct NoCopy{
    NoCopy() = default;  // use the synthesized default constructor
    NoCopy(const NoCopy&) = delete;  // no copy
    NoCopy& operator=(const NoCopy&) = delete;  // no assignment
    ~NoCopy() = default;  // use the synthesized destructor
    // other members;
};
```

2. 如果你设计一个类，不允许 Dtor

```cpp
struct NoDtor {
    NoDtor() = default;  // use the synthesized default constructor
    ~NoDtor() = delete;  // we can't destory objects of type NoDtor
};

NoDtor nd;  // error: NoDtor destructor is deleted
NoDtor *p = new NoDtor();  // ok, but we can't delete p
delete p;  // error: NoDtor destructor is deleted
```

*一般不这么用。*

3. 相对于`1`的改变

```cpp
struct PrivateCopy{
private:
    PrivateCopy(const PrivateCopy&);
    PrivateCopy& operator=(const PrivateCopy&);
public:
    PrivateCopy() = default;
    ~PrivateCopy();
};
```

此class 不允许被 ordinary user code copy, 但仍可被 `friends`, `members copy`。


实际应用: boost 库内有一个类 `noncopyable`

```cpp
namespace boost
{
    namespace noncopyable_
    {
        class noncopyable
        {
        protected:
            noncopyable() {}
            ~noncopyable() {}
        private:
            noncopyable(const noncopyable&);
            const noncopyable& operator=(const noncopyable&);
        };
    }

    typedef noncopyable_::noncopyable noncopyable;
}  // namespace boost
```

以下是测试例子：

```cpp
class A : protected boost::noncopyable
{
public:
    A(int c) : a(c) {}
    int a;
};

int main(int argc, char const* argv[])
{
    A a(1);
    A b = a;  // error
    return 0;
}
```

A 继承自 noncopyable, `A b = a` 时，会调用父类的拷贝构造函数，则会出现不可赋值的错误。


```cpp
class A : protected boost::noncopyable
{
public:
    A(int c) : a(c) {}
    A(const A& rhs) { a = rhs.a; }
    int a;
};

int main(int argc, char const* argv[])
{
    A a(1);
    A b = a;
    return 0;
}
```

A 中overload 之后调用自己的就可以通过编译了。