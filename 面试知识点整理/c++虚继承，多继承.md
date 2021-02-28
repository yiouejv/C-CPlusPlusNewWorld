看这一篇文章之前强烈建议先看以下我之前发布的

<a href="./虚函数，虚表深度剖析">虚指针，虚函数剖析</a>

**例1: 以下代码输出什么？**

```cpp
#include <iostream>
using namespace std;


class A 
{
protected:
    int m_data;
public:
    A(int data = 0) {m_data=data;}
    int GetData() { return doGetData(); }
    virtual int doGetData() { return m_data; }
};

class B : public A
{
protected:
    int m_data;
public:
    B(int data = 1) { m_data = data; }
    int doGetData() { return m_data; }
};

class C: public B
{
protected:
    int m_data;
public:
    C(int data=2) { m_data = data; }
};

int main(int argc, char const *argv[])
{
    C c(10);

    cout << c.GetData() << endl;
    cout << c.A::GetData() << endl;
    cout << c.B::GetData() << endl;
    cout << c.C::GetData() << endl;
    cout << c.doGetData() << endl;
    cout << c.A::doGetData() << endl;
    cout << c.B::doGetData() << endl;
    cout << c.C::doGetData() << endl;
    return 0;
}
```

构造函数从最初始的基类开始构造，各个类的同名变量没有形成覆盖，都是单独的变量。 

理解这两个重要的C++特性后解决这个问题就比较轻松了。 下面我们详解这几条输出语句。

`cout << c.GetData() << endl;` 本来是要调用C类的 GetData(), C中未定义， 故调用 B 中的， 但是 B 中也未定义， 故调用 A 中的 GetData()， 因为 A 中的 doGetData()是虚函数，所以调用 B 类中的 doGetData(),而 B 类的 doGetData() 返回 B::m_data, 故输出1。

`cout << c.A::GetData() << endl;` 因为 A 中的 doGetData() 是虚函数，又因为 C 类中未重定义该接口，所以调用 B 类中的 doGetData()， 而 B 类的 doGetData() 返回 B::m_data, 故输出 l 。

`cout << c.B::GetData() << endl;` C调用哪一个GetData() 本质上都是调用的A::GetData(), 调用到 doGetData() 虚函数，再调用父类B覆盖后的虚函数，返回B::m_data, 所以前5个都是1

`cout << c.A::doGetData() << endl;` 显示调用A::doGetData(), 返回 A::m_data, 是0

`cout << c.B::doGetData() << endl;`, `cout << c.C::doGetData() << endl;` 都将调用B::doGetData(), 返回B::m_data, 是1

所以结果为: 1 1 1 1 1 0 1 1

方便排版，请忽略掉换行。

最后附上内存结构图:

<img src="../images/oop2_1.png">

**例2: 为什么虚函数效率低？**

因为虚函数需要一次间接的寻址，而普通的函数可以在编译时定位到函数的地址，虚函数是要根据虚指针定位到函数的地址。多增加了一个过程，效率肯定低一些，但带来了运行时的多态。

----------------------------

C++支持多重继承，从而大大增强了面向对象程序设计的能力。多重继承是一个类从多个基类派生而来的能力，派生类实际上获取了所有基类的特性。当一个类是两个或多个基类的派生类时，必须在派生类名和冒号之后，列出所有基类的类名，基类间用逗号隔开。 **派生类的构造函数必须激活所有基类的构造函数，并把相应的参数传递给它们**。派生类可以是另一个类的基类，这样，相当于形成了一个继承链。当派生类的构造函数被激活时，它的所有基类的构造函数也都会被激活。 

在面向对象的程序设计中，继承和多重继承一般指公共继承。 在无继承的类中，protected 和 private 控制符是没有差别的，在继承中，基类的 private 对所有的外界都屏蔽（包括自己的派生类）， 基类的 protected 控制符对应用程序是屏蔽的， 但对其派生类是可访问的。

------------------------------------

### 虚继承

什么是虚继承？它与一般的继承有什么不同？它有什么用？

虚拟继承是多重继承中特有的概念。 虚拟基类是为解决多重继承而出现的。 请看下图：

<img src="../images/oop2_2.png">

类D继承自类B和类C, 而类B和类C都继承自类A.

在类D中会两次出现A。为了节省内存空间，可以将B、C对A 的继承定义为虚拟继承，而A就成了虚拟基类。 最后形成如下图所示的情况：

<img src="../images/oop2_3.png">

```cpp
代码如下：
class A; 
class B : public virtual A;
class C : public virtual A;
class D : public B, public C;
```

注意： 虚函数继承和虚继承是完全不同的两个概念.


### 多重继承

**例3: 请评价多重继承的优点和缺陷。**

多重继承在语言上并没有什么很严重的问题，但是标准本身只对语义做了规定，而对编译器的细节没有做规定。所以在使用时（即使是继承），最好不要对内存布局等有什么假设。为了避免由此带来的复杂性，通常推荐使用复合。

1. 多重继承本身并没有问题，不过大多数系统的类层次往往有一个公共的基类，而这样的结构如果使用多重继承，稍有不慎，将会出现一个严重现象————菱形继承，这样的继承方式会使得类的访问结构非常复杂。 但并非不可处理，可以用virtual继承（并非唯一的方法）
2. 从哲学上来说，C++多重继承必须要存在，这个世界本来就不是单根的。从实际用途上来说，多重继承不是必需的。
3. 多重继承在面向对象理论中并非是必要的————因为它不提供新的语义，可以通过单继承与复合结构来取代。 而Java则放弃了多重继承，使用简单的interface取代。 因为C++中没有interface这个关键字，所以不存在所谓的“接口”技术。但是C++可以很轻松地做到这样的模拟，因为C++中的不定义属性的抽象类就是接口。
4. 多重继承本身并不复杂，对象布局也不混乱，语言中都有明确的定义。真正复杂的是使用了运行时多态(virtual)的多重继承（因为语言对于多态的实现没有明确的定义）。 

5. 要了解C++，就要明白有很多概念是C++ 试图考虑但是最终放弃的设计。你会发现很多Java、C＃中的东西都是C++考虑后放弃的。

不是说这些东西不好，而是在C++中它将破坏C++作为一个整体的和谐性，或者C++ 并不需要这样的东西。 

举个例子来说明，C#中有一个关键字base用来表示该类的父类，C++却没有对应的关键字。为什么没有？其实C++中曾经有人提议用一个类似的关键字 inherited, 来表示被继承的类，即父类。 这样一个好的建议为什么没有被采纳呢？因为这样的关键字既不必须又不充分。 不必须是因为 C++有一个 `typedef* inherited`，不充分是因为有多个基类，你不可能知道 inherited 指的是哪个基类。


**例4: 在多继承的时候，如果一个类继承同时继承自 class A 和 class B, 而 class A 和 B 中都有一个函数叫 foo()， 如何明确地在子类中指出调用是哪个父类的 foo()?**

```cpp
class A
{
public:
    void foo() { cout << "A foo" << endl; }
};

class B
{
public:
    void foo() { cout << "B foo" << endl; }
};

class C : public A, public B
{

};

int main(int argc, char const* argv[])
{
    C c;
    c.A::foo();
    return 0;
}
```

C 继承自 A 和 B, 如果出现了相同的函数foo()， 那么C.A::foo(), C.B::foo() 就分别代表从 A 类中继承的 foo 函数和从 B 类中继承的 foo 函数。

**例5: 以下代码输出什么？**

```cpp
class A
{
    int m_nA;
};

class B
{
    int m_nB;
};

class C : public A, public B
{
    int m_nC;
};

int main(int argc, char const* argv[])
{
    C* pC = new C;
    B* pB = dynamic_cast<B*>(pC);
    A* pA = dynamic_cast<A*>(pC);
    cout << (pC == pB) << endl;
    cout << (pC == pA) << endl;
    cout << ((int)pC == (int)pB) << endl;
    cout << ((int)pC == (int)pA) << endl;
    return 0;
}
```

当进行pC=pB比较时，实际上是比较pC指向的对象和隐式转换pB后pB 指向的对象 (pC指向的对象）的部分，这个是同一部分，是相等的。

但是，pB实际上指向的地址是对象C中的父类B部分，从地址上跟pC不一样，所以直接比较地址数值的时候是不相等的。

内存结构图如下:

<img src="../images/oop2_4.png">


**例6: 如果鸟是可以飞的，那么驼鸟是鸟么？驼鸟如何继承鸟类？**

鸟是可以飞的。 也就是说，当鸟飞行时，它的高度是大于0的。 驼鸟是鸟类（生物学上）的一种， 但它的飞行高度为0（驼鸟不能飞）。

不要把可替代性和子集相混淆。 即使驼鸟集是鸟集的一个子集（每个驼鸟集都在鸟集内），但并不意味着鸵鸟的行为能够代替鸟的行为。 可替代性与行为有关，与子集没有关系。 当评价一个潜在的继承关系时，重要的因素是可替代的行为，而不是子集。

如果一定要让驼鸟来继承鸟类， 可以采取组合的办法， 把鸟类中的可以被驼鸟继承的函数挑选出来，这样驼鸟就不是"a kind of"鸟了，而是"has some kind of"鸟的属性而已。 

```cpp
class bird
{
public:
    void eat();
    void sleep();
    void fly();
};

class ostrich
{
public:
    void eat();
    void sleep();
};
```

**例6: C++中如何阻止一个类被实例化？**

使用抽象类，或者构造函数被声明成private。


--------------------

最后补充两个知识点:

函数的隐藏和覆盖

- 函数的隐藏: 没有定义多态的情况下，即没有加virtual的前提下，如果定义了父类和子类，父类和子类出现了同名的函数，就称子类的函数把同名的父类的函数给隐藏了。
- 函数的覆盖：是针对多态来说的。 如果定义了父类和子类，父类中定义了公共的虚函数，如果此时子类中没有定义同名的虚函数，那么在子类的虚函数表中将会写上父类的该虚函数的函数入口地址，如果在子类中定义了同名虚函数的话，那么在子类的虚函数表中将会把原来的父类的虚函数地址覆盖掉，覆盖成子类的虚函数的函数地址。

总结: 本文的重点还是承接之前“虚指针，虚表剖析”的内容，对于多重继承，没有探究其内存结构，并且也不是很好弄清楚，其功能大多数可以被组合(composition)的方式实现，C++标准没有给出编译器具体的多继承的实现细节，不同的编译器有不同的做法。

