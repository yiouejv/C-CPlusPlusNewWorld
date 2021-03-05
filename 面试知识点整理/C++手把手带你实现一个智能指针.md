
为什么需要智能指针？

这个问题承接上一篇文章《C++ 堆，栈，RAII》，在RAII的指引下，我们需要实现一个类来管理资源，将资源和类对象的生命周期进行绑定，这样我们就可以不用手动释放资源了。

那为什么把类实现成 `like pointer`?

上篇文章中说道，因为C++存在对象切片，而使用指针就避免了这个问题。

我们现在来实现一个智能指针:

首先，我们应该满足资源管理的需求: 构造函数获得资源，析构函数释放资源。

```cpp
class Type
{ };

class smart_ptr
{
public:
    smart_ptr(Type* ptr = NULL) : m_ptr(ptr) {}
    ~smart_ptr() {
        delete m_ptr;
    }
private:
    Type* m_ptr;
};

smart_ptr(new Type);
```

好了，我们这样就实现了一个可以管理 Type 类指针的 `smart_ptr`。

显然，我们这个代码不够通用，只能管理 Type这个类型，我们把 smart_ptr 改成模板，把类型传进去，这样就通用了。

```cpp
template<typename T>
class smart_ptr
{
public:
    smart_ptr(T* ptr = NULL) : m_ptr(ptr) {}
    ~smart_ptr() {
        delete m_ptr;
    }
private:
    T* m_ptr;
};
```

我们只需要把`smart_ptr(new Type);` 改成 `smart_ptr<Type>(new Type);`，就对Type进行了管理。

这样我们就实现了资源管理的功能，下面我们还需要实现`like pointer`功能。

指针有什么操作？

```cpp
T& operator*() const;
T* operator->() const;
operator bool() const;
```

我们需要实现指针的解引用，`->` 运算, `bool`运算, `bool`运算这里涉及到一个隐式转换的问题，有机会再说。 注意这里函数括号后面加上`const`，表示当前成员函数不改变对象成员，这是个好习惯，不清楚的话可以看下我之前的文章。

```cpp
template<typename T>
class smart_ptr
{
public:
    smart_ptr(T* ptr = NULL) : m_ptr(ptr) {}
    ~smart_ptr() {
        delete m_ptr;
    }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    operator bool() const { return m_ptr; }
private:
    T* m_ptr;
};
```

```cpp
// 测试
class Type
{
public:
    int a = 1;
};

smart_ptr<Type> sptr(new Type);
cout << sptr->a << endl;        // 1
cout << (*sptr).a << endl;      // 1
if (sptr) {                     // true
    cout << "true" << endl;
}
```

这样，我们就初步实现了指针的这几个行为。

------------

一般类内包含一个指针，这种设计叫委托，类的功能基本上都是由类内这个指针来完成的，可以理解为委托它实现的。

**类内包含指针的话，就少不了三个函数，拷贝构造，拷贝赋值，析构函数。**

有指针存在，就涉及到浅拷贝还是深拷贝的问题，如果不写拷贝构造，用到了拷贝函数时，编译器会提供一个默认的拷贝构造，而这个默认的拷贝构造做的事情是把你的成员变量逐个拷贝下来。

显然，类内的指针就被copy了一份，新的对象中就有一个新拷贝的指针了，然而这个指针和被拷贝的对象里的指针一样，都是指向原指针的地址。 如果原对象指针所指的空间被释放了，这个拷贝对象指针再去操作这块空间，结果可想而知。

所以，有指针的话则需要我们手动去定义一个拷贝构造，在拷贝构造内申请空间，把原指针的内存空间copy过来，新对象里的指针指向这块空间。

拷贝赋值的操作是这样的: `b = a;` 把 a的值赋值给b，首先我得把b内指针占用的空间给释放掉，再把a内指针指向的空间拷贝一份，再将b内指针指过去，这样就完成了拷贝赋值，这里有个问题值得注意的是，如果 b 和 a指向的是同一片区域，相当于把自己赋值给自己，根据上面的操作，先把内存给释放了，在下一步拷贝时则会引发异常，所以，我们在释放空间之前，得先判断一下咱是不是自己啊！

析构函数就很好理解了，有指针指向堆空间，最后肯定要在析构函数内释放内存啦。

所以，类内包含指针的话这三个函数缺一不可，其他的函数则根据需要进行补充。

------------------

现在回归我们的话题，智能指针需要实现拷贝构造，拷贝赋值吗？

最简单的方式就是禁用拷贝构造，拷贝赋值。 如果我们不写拷贝构造，拷贝赋值，编译器就会提供一个默认的浅拷贝，我们一用，就会两次析构同一块内存引发异常。 就像下面这样:

```cpp
class Type
{
public:
    int a = 1;
};

template<typename T>
class smart_ptr
{
public:
    smart_ptr(T* ptr = NULL) : m_ptr(ptr) {}
    ~smart_ptr() {
        delete m_ptr;
    }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    operator bool() const { return m_ptr; }
private:
    T* m_ptr;
};

int main()
{
    smart_ptr<Type> sptr(new Type);
    smart_ptr<Type> sptr2(sptr);
    return 0;
}
```

所以，我们需要显式把这两个函数给删掉，C++11 提供的 `=delete` 就可以用上了

```cpp
class Type
{
public:
    int a = 1;
};

template<typename T>
class smart_ptr
{
public:
    smart_ptr(T* ptr = NULL) : m_ptr(ptr) {}
    ~smart_ptr() {
        delete m_ptr;
    }
    // 加上下面这两行
    smart_ptr(const smart_ptr&) = delete;
    smart_ptr& operator=(const smart_ptr) = delete;

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    operator bool() const { return m_ptr; }
private:
    T* m_ptr;
};

int main()
{
    smart_ptr<Type> sptr(new Type);
    smart_ptr<Type> sptr2(sptr);  // 这行就直接编译不过了
    return 0;
}
```

这样就杜绝了这两个函数被调用。

第二种方案，我们需要去实现拷贝构造和拷贝赋值，问题是要怎么实现这两个函数，我们要不要在智能指针拷贝时把对象拷贝一份？ 

不行，通常大家都不会这么用，因为使用智能指针的目的就是要减少对象的拷贝，所以我们要实现拷贝就有两种方式了。

1. 在拷贝里面实现搬移的操作，把原指针的对象赋值给新指针，原指针就不能再用了，对应 `std::unique_ptr`
2. 原指针和新指针都指向那一个对象，在智能指针里添加一个引用计数，引用计数为0后删除该对象，对应 `std::shared_ptr`

下面我们实现一个搬移的操作。

```cpp
#include <iostream>
using namespace std;

class Type
{
public:
    int a = 1;
};

template<typename T>
class smart_ptr
{
public:
    smart_ptr(T* ptr = NULL) : m_ptr(ptr) {}
    ~smart_ptr() {
        delete m_ptr;
    }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    operator bool() const { return m_ptr; }

    // 搬移构造
    smart_ptr(smart_ptr&& rhs) noexcept {
        m_ptr = rhs.m_ptr;
        rhs.m_ptr = NULL;
    }
    // 搬移赋值
    smart_ptr& operator=(smart_ptr&& rhs) noexcept {
        m_ptr = rhs.m_ptr;
        rhs.m_ptr = NULL;
        return *this;
    }
private:
    T* m_ptr;
};

int main()
{
    smart_ptr<Type> sptr(new Type);
    smart_ptr<Type> sptr2(std::move(sptr));  // 调用搬移构造
    smart_ptr<Type> sptr3;
    sptr3 = std::move(sptr2);  // 调用搬移赋值
    return 0;
}
```

根据C++的规则，我们提供了搬移构造而没有提供拷贝构造，那拷贝构造就自动被禁用。

搬移构造需要的参数是一个右值，我们借用标准库的 `std::move()` 函数让它帮我们把 `sptr` 转型为一个右值，我们在构造函数内把 rhs的指针给拿过来，再把rhs指向空，这时rhs以后再也不能被用了，因为它的资源已经被我偷过来了。 类似的，搬移赋值也是一样的道理。

如果你发现我在`move function` 后加了 `noexcept` 关键字，这对于智能指针能被正确使用是十分必要的，我会在以后的文章中说明。

这样我们就基本实现了一个 `unique_ptr` 的功能。

`unique_ptr` 算是一种较为安全的智能指针了。 但是，一个对象只能被单个 `unique_ptr` 所拥有，这显然不能满足所有使用场合的需求。 一种常见的情况是，多个智能指针同时拥有一个对象；当它们全部都失效时，这个对象也同时会被删除。这也就是 `shared_ptr` 了。`unique_ptr` 和 `shared_ptr` 的主要区别如下图所示：

<img src="./images/smart_ptr1.png">

多个不同的 `shared_ptr` 不仅可以共享一个对象，在共享同一对象时也需要同时共享同一个计数。 当最后一个指向对象（和共享计数）的 `shared_ptr` 析构时，它需要删除对象和共享计数。 我们下面就来实现一下。

我们需要实现一个`share_count` 类，用来处理引用计数增加减少的操作，这里没有考虑计数器的线程安全性。

```cpp
class share_count {
public:
    share_count() : _count(1) {}
    void add_count() {
        ++_count;
    }
    long reduce_count() {
        return --_count;
    }
    long get_count() const {
        return _count;
    }
private:
    long _count;
};
```

下面我们实现一下构造函数，拷贝构造，拷贝赋值，析构函数，具体实现如下。

```cpp
class Type
{
public:
    int a = 1;
};

class share_count {
public:
    share_count() : _count(1) {}
    void add_count() {
        ++_count;
    }
    long reduce_count() {
        return --_count;
    }
    long get_count() const {
        return _count;
    }
private:
    long _count;
};

template<typename T>
class smart_ptr
{
public:
    smart_ptr(T* ptr = NULL) : m_ptr(ptr) {
        if (ptr) {
            m_share_count = new share_count;
        }
    }
    ~smart_ptr() {
        if (m_ptr && !m_share_count->reduce_count()) {
            delete m_ptr;
            delete m_share_count;
            cout << "~smart_ptr" << endl;
        }
    }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    operator bool() const { return m_ptr; }

    smart_ptr(const smart_ptr& rhs) noexcept {
        m_ptr = rhs.m_ptr;
        m_share_count = rhs.m_share_count;
        m_share_count->add_count();
    }
    smart_ptr& operator=(const smart_ptr& rhs) noexcept {
        m_ptr = rhs.m_ptr;
        m_share_count = rhs.m_share_count;
        m_share_count->add_count();
        return *this;
    }
    long use_count() const {
        if (m_ptr) {
            return m_share_count->get_count();
        }
        return 0;
    }
private:
    T* m_ptr;
    share_count* m_share_count;
};

int main()
{
    smart_ptr<Type> sptr(new Type);
    cout << "sptr's share_count：" << sptr.use_count() << endl;

    smart_ptr<Type> sptr2(sptr);
    cout << "sptr's share_count：" << sptr2.use_count() << endl;

    smart_ptr<Type> sptr3;
    sptr3 = sptr2;
    cout << "sptr's share_count：" << sptr3.use_count() << endl;
    return 0;
}
```

```
sptr's share_count： 1
sptr's share_count： 2
sptr's share_count： 3
~smart_ptr
```

我们看到最后被正确的执行析构了，这样我们就基本实现了一个 `shared_ptr` 的功能了。

智能指针浅显的写法就模拟到这里了，可能在具体的场景下还缺少一些功能，根据需求我们可以再增加嘛！

好了，智能指针先说到这里了，如果文章有错误的地方还请给我指出来，大家一起进步嘛。

如果觉得对你有帮助的话请@程序员杨小哥 点个赞，谢谢！

