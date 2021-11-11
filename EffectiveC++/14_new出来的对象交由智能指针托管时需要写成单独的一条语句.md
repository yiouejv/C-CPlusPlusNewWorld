
new 出来的对象交由智能指针托管时需要写成单独的一条语句。

否则可能会出现内存泄漏。

```C++
#include<iostream>
using namespace std;

class A {
public:
    A() {
        cout << "A" << endl;
    }
    ~A() {
        cout << "~A" << endl;
    }
};

int f2() {
    return 0;
}

void f(auto_ptr<A> p = auto_ptr<A>(new A), int a = f2()) {

}


int main(int argc, char const* argv[])
{
    f();
    return 0;
}
```

看这个例子。

函数f有两个参数 第一个参数是一个智能指针对象。

管理的资源的A类型的指针。

第二个参数是整型 取值依赖于函数的返回值。

在执行函数f之前需要做三件事。

执行函数f2 new A 调用智能指针的构造函数。

这三件事的执行顺序C++给了编译器很强的自由度。

也就是说顺序不保证。

如果函数f2正常返回没什么问题。

<img src="./images/14_01.png">

可以看到类A的构造析构函数被正确的调用。

一旦函数f2抛出异常 则new A 返回的指针就丢失了。

从而造成了内存泄漏。

注意这里 我说的是new A 返回的指针丢失了。

指针丢了就没办法释放内存了。

```C++
#include<iostream>
using namespace std;

class A {
public:
    A() {
        cout << "A" << endl;
    }
    ~A() {
        cout << "~A" << endl;
    }
};

int f2() {
    throw;
    return 0;
}

void f(auto_ptr<A> p = auto_ptr<A>(new A), int a = f2()) {

}


int main(int argc, char const* argv[])
{
    f();
    return 0;
}
```

<img src="./images/14_02.png">

如果单独写成一条语句

那么将保证了 new A 和 auto_ptr 的构造是一块被调用的，中间肯定不会被打断。


