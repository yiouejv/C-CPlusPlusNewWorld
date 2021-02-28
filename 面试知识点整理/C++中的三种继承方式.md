
### public 方式继承

基类成员对派生类的可见性对**派生类**来说，基类的公有成员和保护成员可见，基类的公有成员和保护成员作为派生类的成员时，它们都保持原有的状态;基类的私有成员不可见，基类的私有成员仍然是私有的，派生类不可访问基类中的私有成员。

基类成员对派生类对象的可见性对**派生类对象**来说，基类的公有成员是可见的，其他成员是不可见的。

所以，在公有继承时，派生类的对象可以访问基类中的公有成员，派生类的成员函数可以访问基类中的公有成员和保护成员。

简单来说，派生类能访问基类的public, protected成员，继承过来权限不变，派生类对象只能访问基类public成员。

测试代码如下:

```cpp
class A
{
private:
    int m_data1;
    void print1() { cout << "private print1" << endl; }
protected:
    int m_data2;
    void print2() { cout << "protected print2" << endl; }
public:
    A(int x = 1, int y = 2, int z = 3) : m_data1(x), m_data2(y), m_data3(z) {}
    int m_data3;
    void print3() { cout << "protected print3" << endl; }
};

class B : public A
{
public:
    void test_public() {
        cout << m_data3 << endl;
        print3();
    }
    void test_protected() {
        cout << m_data2 << endl;
        print2();
    }
    void test_private() {
        // 下面两行编译不过，B类内无法访问父类的私有成员
        // cout << m_data1 << endl;  
        // print1();
    }
};


int main(int argc, char const* argv[])
{
    B b;
    b.test_public();
    b.test_protected();
    b.test_private();
    cout << b.m_data3 << endl;
    // cout << b.m_data2 << endl;  // 编译不过，子类对象无法访问父类protected的成员
    // cout << b.m_data1 << endl;  // 编译不过，子类对象无法访问父类private的成员
    return 0;
}
```

### private 方式继承

基类成员对其对象的可见性与一般类及其对象的可见性相同，公有成员可见，其他成员不可见

基类成员对派生类的可见性对**派生类**来说，基类的公有成员和保护成员是可见的，基类的公有成员和保护成员都作为派生类的私有成员，并且不能被这个派生类的子类所访问；基类的私有成员是不可见的，派生类不可访问基类中的私有成员。

基类成员对派生类对象的可见性对**派生类对象**来说，基类的所有成员都是不可见的。所以，在私有继承时，基类的成员只能由直接派生类访问,而无法再往下继承。

简单来说派生类可以访问基类的public, protected成员，继承过来之后变成自己私有的。 派生类的对象啥都不能访问。

```cpp
class A
{
private:
    int m_data1;
    void print1() { cout << "private print1" << endl; }
protected:
    int m_data2;
    void print2() { cout << "protected print2" << endl; }
public:
    A(int x = 1, int y = 2, int z = 3) : m_data1(x), m_data2(y), m_data3(z) {}
    int m_data3;
    void print3() { cout << "protected print3" << endl; }
};

class B : private A
{
public:
    void test_public() {
        cout << m_data3 << endl;
        print3();
    }
    void test_protected() {
        cout << m_data2 << endl;
        print2();
    }
    void test_private() {
        // 下面两行编译不过，B类内无法访问父类的私有成员
        // cout << m_data1 << endl;  
        // print1();
    }
};


int main(int argc, char const* argv[])
{
    B b;
    b.test_public();
    b.test_protected();
    b.test_private();
    // cout << b.m_data3 << endl;  // // 编译不过，子类对象无法访问父类public的成员
    // cout << b.m_data2 << endl;  // 编译不过，子类对象无法访问父类protected的成员
    // cout << b.m_data1 << endl;  // 编译不过，子类对象无法访问父类private的成员
    return 0;
}
```

### protected 方式继承

基类成员对派生类的可见性对**派生类**来说，基类的公有成员和保护成员是可见的，基类的公有成员和保护成员都作为派生类的保护成员，并且不能被这个派生类的子类的对象所访问，但可以被派生类的子类所访问；基类的私有成员是不可见的，派生类不可访问基类中的私有成员。

基类成员对派生类对象的可见性对派生类对象来说，基类的所有成员都是不可见的。

简单来说: 派生类可以访问基类的public, protected，继承过来都变成了protected，派生类对象啥都不能访问。

**总结**

对于这三种方式继承的**派生类**来说: 都能访问基类的public, protected 成员;

public 的方式继承到派生类，这些成员的权限和在基类里的权限保持一致;   
protected方式继承到派生类，成员的权限都变为protected;   
private 方式继承到派生类，成员的权限都变为private;   

对于三种方式**派生类的对象**来说: 只有public的方式继承后，派生来的对象只能访问基类的public成员，protected和private方式继承，派生类的对象都不可以访问父类的成员。


**例: 请考虑标记为A到J的语句在编译时可能出现的情况。**

```cpp
#include<iostream>
#include<cstdio>

class Parent
{
public:
    Parent(int var=-1) {
        m_nPub = var;
        m_nPtd = var;
        m_bPrt = var;
    }
    int m_nPub;
protected:
    int m_nPtd;
private:
    int m_nPrt;
};

class Child1 : public Parent
{
public:
    int GetPub() { return m_nPub; }
    int GetPtd() { return m_nPtd; }
    int GetPrt() { return m_nPrt; }
    // A
};

class Child2 : protected Parent
{
public:
    int GetPub() { return m_nPub; }
    int GetPtd() { return m_nPtd; }
    int GetPrt() { return m_nPrt; }
    // B
};

class Child3 : private Parent
{
public:
    int GetPub() { return m_nPub; }
    int GetPtd() { return m_nPtd; }
    int GetPrt() { return m_nPrt; }
    // C
};

int main(int argc, char const *argv[])
{
    Child1 cd1;
    Child2 cd2;
    Child3 cd3;

    int nVar = 0;

    // public inherited
    cd1.m_nPub = nVar; // D
    cd1.m_nPtd = nVar; // E
    nVar = cd1.GetPtd(); // F

    // protected inherited
    cd2.m_nPub = nVar; // G
    nVar = cd2.GetPtd(); // H

    // private inherited
    cd3.m_nPub = nVar; // I
    nVar = cd3.GetPtd();  // J
    return 0;
}
```

A, B, C都错误，因为 m_nPrt 是父类的private变量，子类不能访问。

D正确。 cdl是公有继承，可以访问并改变父类的公有变量。

E 错误。 m_nPtd 是父类 Parent 的保护变量，不可以被公有继承的 cdl 访问， 更不可以被修改。 虽然 m_nPtd 是父类 Parent 的保护变量，经过公有继承后， m_nPtd 在子类中依然是protected, 而子类的对象cdl是不能访问自身的protected成员，只能访问public成员。

F正确。派生类内可以访问父类的保护变量。

G错误。cd2是保护继承的，派生类对象不能访问父类成员。

H正确。派生类内可以访问父类的保护变量。

I错误。cd2是私有继承的，派生类对象不能访问父类成员。

J正确。派生类内可以访问父类的保护变量。
