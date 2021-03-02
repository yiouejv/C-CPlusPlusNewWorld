

RTTI 是 Run Time Type Information 的缩写，从字面上来理解就是执行时期的类型信息，其重要作用就是动态判别执行时期的类型。

并不是说这篇文章是RTTI，和用于RTTI的四种类型转换，而是介绍RTTI，再介绍一下4种类型转换，因为RTTI有用到其中一种类型转换，所以相当于两篇文章写在一起。

实际上 RTTI 用到的是`typeid()` 和 `dynamic_cast()`。

**为什么会有RTTI？**

C++是一种静态类型语言，其数据类型是在编译期就确定的，不能在运行时更改。然而由于面向对象程序设计中多态性的要求，C++中的指针或引用(Reference)本身的类型，可能与它实际代表(指向或引用)的类型并不一致。有时我们需要将一个多态指针转换为其实际指向对象的类型，就需要知道运行时的类型信息，这就产生了运行时类型识别的要求。

实事求是地讲，RTTI是有用的。 但因为一些理论上及方法论上的原因，它破坏了面向对象的纯洁性。

首先， 它破坏了抽象，使一些本来不应该被使用的方法和属性被不正确地使用。

其次，因为运行时类型的不确定性，它把程序变得更脆弱。

第三点，也是最重要的一点，它使程序缺乏扩展性。 当加入了一个新的类型时，你也许需要仔细阅读你的`dynamic_cast`的代码，必要时改动它们，以保证这个新的类型的加入不会导致问题。 而在这个过程中，编译器将不会给你任何帮助。

总的来说，RTTI 因为它的方法论上的一些缺点，它必须被非常谨慎地使用。 今天面向对象语言的类型系统中的很多东西就是产生于避免RTTI的各种努力。

---------------------------

首先我们来个例子感受一下:

```cpp
#include<iostream>
#include<typeinfo>
using namespace std;

class Base
{
public:
    virtual void funcA() { cout << "Base" << endl; }
};

class Derived : public Base
{
public:
    virtual void funcB() { cout << "Derived" << endl; }
};

void funcC(Base* p)
{
    Derived* dp = dynamic_cast<Derived*>(p);
    if (dp != NULL) {
        dp->funcB();
    }
    else {
        p->funcA();
    }
};

void funcD(Base* p)
{
    Derived* dp = NULL;
    if (typeid(*p) == typeid(Derived))
    {
        dp = static_cast<Derived*>(p);
        dp->funcB();
    }
    else {
        p->funcA();
    }
}

int main(int argc, char const* argv[])
{
    Base* p = new Derived;
    cout << typeid(p).name() << endl;
    cout << typeid(*p).name() << endl;
    funcD(p);
    funcC(p);
    delete p;

    Base* dp = new Base;
    funcC(dp);
    funcD(dp);
    delete dp;
    return 0;
}
```

funcC是用`dynamic_cast`类型转换是否成功来识别类型的，`dynamic_cast`操作符将基类类型对象的引用或指针转化为同一继承层次中的其他类型的引用或指针。 

如果绑定到引用或指针的对象不是目标类型的对象，则`dynamic_cast`失败。   
如果转换到指针类型的`dynamic_cast`失败，则`dynamic_cast`的结果是`NULL`值;  
如果转换到引用类型的`dynamic_cast`失败， 则抛出一个`bad_cast`类型的异常  

funcD是用`typeid`判断基类地址是否一致的办法来识别类型的。

-------------------------------
### typeid

下面我们具体说说 `typeid`

`typeid`是C++的关键字之一, 等同于`sizeof`这类operator。 typeid 操作符的返回结果是名为 `type_info`的标准库类型的对象的引用，在头文件typeinfo 中定义。 有两种形式:

1. typeid(type)
2. typeid(expression)

表达式的类型是类类型，且至少含有一个虚函数，则typeid操作符返回表达式的动态类型，需要在运行时计算，否则返回表达式的静态类型，在编译时就可以计算。

C++标准规定了其实现必须提供如下四种操作:

1. t1 == t2: 如果两个对象t1和t2类型相同，则返回true;否则返回false
2. t1 != t2: 如果两个对象t1和t2类型不同，则返回true;否则返回false
3. t.name(): 返回类型的c-style字符串，类型名字用系统相关的方法产生
4. t1.before(t2): 返回指出t1是否出现在t2之前 的bool值

`type_info`类提供了public虚析构函数，以使用户能够用其作为基类。它的默认构造函数和复制构造函数及赋值操作符都定义为private，所以不能定义或复制type_info 类型的对象。 程序中创建type_info对象的唯一方法是使用typeid操作符。 由此可见，如果把typeid看作函数的话，其应该是type_info的友元。 这具体由编译器的实现所决定，标准只要求实现为每个类型返回唯一的字符串。

**例1: C++里面的typeid运算符返回值是什么？**

答: 常量对象的引用。

如果p是基类指针，并且指向一个派生类型的对象，并且基类中有虚函数，那么`typeid(*p)`返回p所指向的派生类类型，`typeid(p)`返回基类类型。

**RTTI的实现原理**: 通过在虚表中放一个额外的指针，每个新类只产生一个typeinfo实例，额外指针指向typeinfo, typeid返回对它的一个引用。

-----------------------------
    
### static_cast

`static_cast < new_type > ( expression ) `

本来应该先讨论`dynamic_cast`的，因为咱们本来聊的RTTI嘛，但是先了解一下`static_cast`，然后看和`dynamic_cast`的比较可能更好一点。

使用场景:

1. 基本数据类型之间的转换
2. initializing conversion

```cpp
int n = static_cast<int>(3.14);
cout << "n = " << n << '\n';
vector<int> v = static_cast<vector<int>>(10);
cout << "v.size() = " << v.size() << '\n';
```

3. 类指针或引用向下转换。
4. 将类型转为右值类型，进行move操作，这个在标准库中有体现（放在下一篇文章中解释）

```cpp
vector<int> v = static_cast<vector<int>>(10);
vector<int> v2 = static_cast<vector<int>&&>(v);
cout << "after move, v.size() = " << v.size() << '\n';
cout << v.size() << endl;
```

5. 子类数组指针向上转成父类的指针

```cpp
struct B {
    int m = 0;
    void hello() const {
        cout << "Hello world, this is B!\n";
    }
};
struct D : B {
    void hello() const {
        cout << "Hello world, this is D!\n";
    }
};

D a[10];
B* dp = static_cast<B*>(a);
dp->hello();
```

6. 枚举转换成int or float

```cpp
enum E { ONE = 1, TWO, THREE };
E e = E::ONE;
int one = static_cast<int>(e);
cout << one << '\n';
```

7. int to enum, enum to another emum

```cpp
enum class E { ONE = 1, TWO, THREE };
enum EU { ONE = 1, TWO, THREE };

E e = E::ONE;
int one = static_cast<int>(e);
E e2 = static_cast<E>(one);
EU eu = static_cast<EU>(e2);
```

8. void* to any type

```cpp
int a = 100;
void* voidp = &a;
int *p = static_cast<int*>(voidp);
```

注意：

1. static_cast不能转换掉expression的const、volatile和__unaligned属性,
2. 编译器隐式执行任何类型转换都可由static_cast显示完成

-----------------------

### dynamic_cast

`dynamic_cast < new-type > ( expression )`

接下来是`dynamic_cast`:

动态映射可以映射到中间层级，将派生类映射到任何一个基类，然后在基类之间可以相互映射。

**dynamic_cast实现原理**: 先恢复源指针的RTTI信息，再取目标的RTTT信息，比较两者是否相同，不同取目标类型的基类; 由于它需要检查一长串基类列表，故动态映射的开销比typeid大。 

**dynamic_cast的安全性**: 如实现原理所说，`dynamic_cast`会做一系列的类型检查，转换成功会返回目标类型指针，失败则会返回NULL, 相对于`static_cast`安全，因为 `static_cast`即使转换失败也不会返回NULL。

**例2: 这种情况下 static_cast() 也是安全的。**

```cpp
class Base
{
public:
    void func() { cout << "Base func" << endl; }
};

class Derived : public Base
{
public:
    void func() { cout << "Derived func" << endl; }
};

int main(int argc, char const* argv[])
{
    Derived *pd = new Derived;
    pd->func();
    Base* pb1 = dynamic_cast<Base*>(pd);
    pb1->func();
    Base* pb2 = static_cast<Base*>(pd);
    pb2->func();
    return 0;
}
```

pd 指针指向的内存是子类对象，我们知道，继承子类是包含父类的，相当于在父类的基础上在添加子类的成员（如果你还不清楚的话，建议你看一下我之前的文章: <a href="虚函数，虚表深度剖析.md">虚函数，虚表深度剖析</a>）。 所以pd指针转成父类指针也是没问题的，`static_cast`也一样安全。

相反，如果指针指向的内存是父类成员，转成子类指针，`dynamic_cast` 则会失败，返回NULL, 但是`static_cast`不会失败，强制转过去了，如果此时子类指针访问父类中不存在，但是子类中存在的成员，则会发生意想不到的问题。

看下面这个例子:

```cpp
class Base
{
public:
    virtual void func() { cout << "Base func" << endl; }
};

class Derived : public Base
{
public:
    virtual void func() { cout << "Derived func" << endl; }
    int m_value = 0;
};

int main(int argc, char const* argv[])
{
    Base *pb = new Base;
    pb->func();
    Derived* pd1 = dynamic_cast<Derived*>(pb);
    if (pd1 != NULL) {
        pd1->func();
    } else {
        cout << "dynamic_cast failed" << endl;
    }
    Derived* pd2 = static_cast<Derived*>(pb);
    pd2->func();
    cout << "m_value: " << pd2->m_value << endl;
    return 0;
}
```

输出:

```
Base func
dynamic_cast failed
Base func  // 父类中也有这个虚函数，所以static_cast转换调用没出问题。
m_value: -33686019  // 这里出问题了
```

对于上行转换，`static_cast` 和 `dynamic_cast` 效果一样，都安全, 如果只是单纯的向上转的话，没必要，直接用虚函数实现就好了。

对于下行转换: 你必须确定要转换的数据确实是目标类型的数据，即需要注意要转换的父类类型指针是否真的指向子类对象，如果是，static_cast和dynamic_cast都能成功；如果不是static_cast能返回，但是不安全，可能会出现访问越界错误，而dynamic_cast在运行时类型检查过程中，判定该过程不能转换，返回NULL。

----------------------

### const_cast

`const_cast < new_type > ( expression )`

上面讲了`static_cast`是不能去掉 `const`，而 `const_cast`是专门用来去掉 `const`。

而添加const, `static_cast` 也是可以添加上 const，只是不能去掉const

看下面一个例子:

```cpp
const int a = 26;
const int* pa = &a;
//*pa = 3;  // 编译不过，指针常量不能通过指针修改值

int* b = const_cast<int*>(pa);  // 把const转换掉
*b = 3;

cout << "a: " << a << endl;  // 26
cout << "*b: " << *b << endl;  // 3
```

a 为 `const int` 类型，不可修改，pa 为 `const int*` 类型，不能通过pa指针修改a的值

b 通过 `const_cast` 转换掉了const，成功修改了 a 的值。

<img src="./images/conversion1.png">

有一个问题，为什么a输出是26呢？

如果存在`const int x = 26;` 这种情况，那么编译器会认为x是一个编译期可计算出结果的常量，那么x就会像宏定义一样，用到x的地方会被编译器替换成26。

上述这个例子不建议使用，因为 a 声明为 `const int` 类型，实际上是并不希望被修改的，这样强行修改可能会导致项目里不可预期的错误。

**const_cast 的使用场景**

1. 如果有一个函数，它的形参是non-const类型变量，而且函数不会对实参的值进行改动，这时我们可以使用类型为const的变量来调用函数。

```cpp
void func(int* a)
{ }

int main()
{
    const int a = 26;
    const int* pa = &a;
    func(const_cast<int*>(pa));
}
```

这种情况其实我觉得没必要，实际上我不想改的话，我形参加 const，把前提推翻不就行了，还安全。

2. 定义了一个non-const的变量，却使用了一个指向const值的指针来指向它（这不是没事找事嘛），在程序的某处我们想改变这个变量的值了，但手头只持有指针，这时`const_cast`就可以用到了

```cpp
int a = 26;
const int* pa = &a;
// *pa = 1; 编译不过
int* pa2 = const_cast<int*>(pa);
*pa2 = 1;
```

---------------------

### reinterpret_cast

`reinterpret_cast < new_type > ( expression )`

reinterpret_ cast 通常为操作数的位模式提供较低层的重新解释。

看这个例子:

```cpp
int n = 9; double d = static_cast<double>(n); 
cout << n << " " << d; // 输出9 9

int n2 = 9; double d2 = reinterpret_cast<double&>(n2);
cout << n2 << " " << d2; // 输出9 -9.25596e+61
```

上面的例子中，我们将一个变址从int 转换到 double。这些类型的二进制表达式是不同的。要将整数9转换到双精度整数9, static_cast需要正确地为双精度整数d补足比特位。其结果为9.0。

而 reinterpret_cast 的行为却不同，仅仅是把内存拷贝到目标空间，解释出来是一个大数。

<img src="./images/conversion2.png">

<img src="./images/conversion3.png">

<img src="./images/conversion4.png">

reinterpret_cast这个操作符被用于的类型转换的转换结果几乎都是未知的。

使用 reinterpret_cast 的代码很难移植。转换函数指针的代码是不可移植的，（C++不保证所有的函数指针都被用一样的方法表示），在一些情况下这样的转换会产生不正确的结果。 所以应该避免转换函数指针类型，按照C++新思维的话来说，reinterpret_cast 是为了映射到一个完全不同类型的意思，这个关键词在我们需要把类型映射回原有类型时用到它。
我们映射到的类型仅仅是为了故弄玄虚和其他目的，这是所有映射中最危险的。reinterpret_cast就是一把锐利无比的双刃剑，除非你处于背水一战和火烧眉毛的危急时刻，否则绝不能使用。

其实 `reinterpret_cast` 用法细节还有不少，什么时候需要用到，再去官方了解一下就好了，现在纠的太细意义不大。

