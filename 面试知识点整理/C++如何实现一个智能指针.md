
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

我们只需要把`smart_ptr(new Type);` 改成 `smart_ptr<Type>(new Type);`, 就对Type进行了管理。

这样我们就实现了资源管理的功能，下面我们还需要实现`like pointer`这个现象。

指针有什么操作？

```cpp
T& operator*() const;
T* operator->() const;
operator bool() const;
```

我们需要实现指针的解引用，`->` 运算, `bool`运算, `bool`运算这里涉及到一个隐式转换的问题，有机会再说。 注意这里函数括号后面加上 const, 表示当前函数不改变对象成员，这是个好习惯，不清楚的话可以看下我之前的文章。

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

有指针存在，就涉及到浅拷贝还是深拷贝的问题，如果不写拷贝构造，用到了拷贝函数时，编译器会提供一个默认的拷贝构造，而这个默认的拷贝构造做的事情是把你的成员变量逐个拷贝下来，

显然，类内的指针就被copy了一份，新的对象中就有一个新拷贝的指针了，然而这个指针和被拷贝的对象里的指针一样，都是指向原指针的地址。 如果原对象指针所指的空间被释放了，这个拷贝对象指针再去操作这块空间，结果可想而知。

所以，有指针的话则需要我们手动去定义一个拷贝构造，在拷贝构造内申请空间，把原指针的内存空间copy过来，新对象里的指针指向这块空间。

拷贝赋值的操作是这样的: `b = a;` 把 a的值赋值给b，首先我得把b内指针占用的空间给释放掉，再把a内指针指向的空间拷贝一份，再将b内指针指过去，这样就完成了拷贝赋值，这里有个问题值得注意的是，如果 b 和 a指向的是同一片区域，相当于把自己赋值给自己，根据上面的操作，先把内存给释放了，在下一步拷贝时则会引发异常，所以，我们在释放空间之前，得先判断一下咱是不是自己啊！

析构函数就很好理解了，有指针指向堆空间，最后肯定要在析构函数内释放内存啦。

所以，类内包含指针的话这三个函数缺一不可，其他的函数则根据需要进行补充。

------------------

现在回归我们的话题，


