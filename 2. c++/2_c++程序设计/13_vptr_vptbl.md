


### 虚指针

只要你的对象中有一个虚函数，则你的对象中就一定会有一个指针，虚指针`vptr`。

```cpp
// 演示没有 虚函数的类，类对象大小为成员变量的大小
class A
{
public:
    A() { }
    ~A() { }
    void test() {}
private:
    int m_data1, m_data2;
};


A a;  // sizeof(a) == 8
```


```cpp
// 演示有 虚函数的类，类对象大小为成员变量的大小 + sizeof(vptr)
class A
{
public:
    A() { }
    ~A() { }
    virtual void test() {}
private:
    int m_data1, m_data2;
};


A a;  // sizeof(a) == 12
```

--------------------------

类`B` 继承自类`A`，则将`A`中函数的调用权也一并继承过来了，所以B中也包换了虚函数，对象中也将包含一个`vptr`。

`sizeof(b)`的大小为 自身数据的大小4B，父类数据的大小8B, `vptr` 的大小4B

```cpp

class A
{
public:
    A() { }
    ~A() { }
    virtual void test() {}
private:
    int m_data1, m_data2;
};

class B : public A
{
private:
    int m_data1;
};

B b;  // sizeof(b) == 16
```

### 虚表

```cpp
class A
{
public:
    A() { }
    ~A() { }
    virtual void test() {}
private:
    int m_data1, m_data2;
};

A a
```

`A`类中包含虚函数，有一个虚指针`vptr`, 指向虚表，虚表中存放在类中每一个虚函数的地址。


-----------------------------------
### 多态

我声明一个形状类，接着声明一些具体的形状，圆形，矩形，三角形，我想把它们具体的形状类的对象放在一个`vector`里，那我要指定`vector` 中具体的类型是什么呢？

显然不好指定，因为每个形状的大小是不一样的。 我们可以把`vector`中的类型指定为形状类的指针，指针的大小是一样的，但是每一个指针指向的是一个具体的形状对象。

我每次调用`draw()`函数，希望它能画出具体的某一类形状，三角形画三角形，圆形画圆形。 虽然是同一类指针，但是却表现出不同的状态。 就是多态。


```cpp
#include <iostream>
#include <vector>
using namespace std;

class Shape
{
public:
    virtual void draw() = 0;
};

class Rectangle : public Shape
{
    void draw() { cout << "rectangle" << endl; }
};

class Circle : public Shape
{
    void draw() { cout << "circle" << endl; }
};

class Triangle : public Shape
{
    void draw() { cout << "triangle" << endl; }
};


int main(int argc, char const *argv[])
{
    vector<Shape*> v;
    v.push_back(new Rectangle());
    v.push_back(new Circle());
    v.push_back(new Triangle());
    for (Shape* p : v) {
        p->draw();
    }
    return 0;
}
```

从代码层面来看，p指针指向的是每一个具体形状的类对象，调用`draw()`时调用的都是自己的那一份代码。


**虚函数的使用场景**

一种是上述这种，

二是 <a href="../1_面向对象程序设计/2. class之间的关系.md/#template-method">template-method</a>


