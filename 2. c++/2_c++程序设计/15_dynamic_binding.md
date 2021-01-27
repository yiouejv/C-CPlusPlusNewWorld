
**static binding**

```cpp
#include <iostream>
using namespace std;

class A
{
public:
    virtual void test() { cout << "test A" << endl; }
};

class B : public A
{
public:
    void test() { cout << "test B" << endl; }
};


int main(int argc, char const *argv[])
{
    B b;
    A a = (A) b;
    a.test();  // test A
    return 0;
}
```

`a.test()` 其中`a`是一个对象，不是一个指针，对象是静态绑定。

**dynamic binding**

动态绑定三个条件

1. 是一个指针
2. 向上转型，该指针指向子类对象，指针是父类指针
3. 调用虚函数。

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


