
### const

1. `const` 位于 `*`的左侧: 用来修饰指针所指向的变量，指针指向常量。

```cpp
// 指针不允许改变数据
int b = 500;
const int *a = &b;
*a = 600; // error 
```

```cpp
// 可以通过变量本身去修改
int b = 500;
const int *a = &b;
b = 600;
cout << *a << endl; // 600
```


2. `const` 位于 `*`的右侧: 用来修饰指针本身，指针是常量。

```cpp
// 指针本身是常量，定义时需要初始化
int b = 500;
//int * const a;  // error
int * const c = &b;  // error

*c = 600;  // 正常，允许改值
cout << *c << endl;
```

3. `const` 用在成员函数中, 位于 `function_name () const {}`

我们在定义类的成员函数中，常常有一些成员函数不改变类的数据成员。 也就是说这些函数的 `readonly function`，而有一些函数要修改类的数据成员的值。 如果在`readonly function`都加上`const`进行标识，无疑会提高程序的可读性。 其实还能提高程序的可靠性，已定义成`const`的成员函数，一旦企图改变数据成员的值，则编译器按错误处理。

```cpp
class A
{
public:
    A(int x) : a(x) {}
    int get() const { return a; }
    int get2() const { return a++; }  // ERROR read-only object
private:
    int a;
};

int main(int argc, char const *argv[])
{
    A obj(10);
    cout << obj.get() << endl;
    cout << obj.get2() << endl;
    return 0;
}
```

const 修饰之后，`readonly function` 也将只能调用 `readonly function`, 其实很好理解，如果`readonly function` 函数调用了其他函数，可能数据就会发生变化。

```cpp
class A
{
public:
    A(int x) : a(x) {}
    int get() const { get2(); return a; }  // 错误，不能调用非 readonly function
    int get2() const {}
private:
    int a;
};

int main(int argc, char const *argv[])
{
    A obj(10);
    int b = obj.get();
    cout << b << endl;
    return 0;
}
```

如果类的数据成员加上`mutable`后，修饰为 `const`的成员变量，也可以修改。

```cpp
class A
{
public:
    A(int x) : a(x) {}
    int get() const { return ++a; }
private:
    mutable int a;
};


int main(int argc, char const *argv[])
{
    A obj(10);
    int b = obj.get();
    cout << b << endl;
    return 0;
}
```

4. const 位于函数声明前，意味着函数的返回值是常量


面试时需要注意的是: 面试时应该描述const的`只读`，而不仅仅是常量，关键字const的作用是为读你代码的人传达非常有用的信息。 实际上，声明一个参数为常量是为了告诉用户这个参数的应用目的。 如果你曾花很多时间清理其他人留下的垃圾，你就会很快学会感谢这点儿多余的信息。 当然，懂得用 const 的程序员很少会留下垃圾让别人来清理。 通过给优化器一些附加的信息， 使用关键字const也许能产生更紧凑的代码。
合理地使用关键字const可以使编译器很自然地保护那些不希望被改变的参数， 防止其被无意的代码修改。 简而言之，这样可以减少bug的出现。

### volatile

volatile 关键字是一种类型修饰符，用它声明的类型变量表示可以被某些编译器未知的因素更改，比如：操作系统、硬件或者其它线程等。

遇到这个关键字声明的变量，编译器对访问该变量的代码就不再进行优化。

volatile限定修饰符的用法与const非常相似都是作为类型的附加修饰符。例如：

```cpp
volatile int display_register;
volatile Task *curr_task;
volatile int ixa[ max_size ];
volatile Screen bitmap_buf;
```

display_register是一个int型的volatile对象;    
curr_task是一个指向volatile的Task类对象的指针;   
ixa是一个volatile的整型数组，数组的每个元素都被认为是volatile的;   
bitmap_buf 是一个volatile的Screen类对象，它的每个数据成员都被视为volatile的。

volatile的语法与const是一样的，但是volatie的意思是“在编译器认识的范围外，这个数据可以被改变”。不知什么原因，环境正在改变数据（可能通过多任务处理），所以，volatile告诉编译器不要擅自做出有关数据的任何假定，在优化期间这是特别重要的。如果编译器说：我已经把数据读进寄存器，而且再没有与寄存器接触。”在一般情况下，它不需要再读这个数据。但是，如果数据是volatile修饰的，编译器则不能做出这样的假定，因为数据可能被其他进程改变了，编译器必须重读这个数据而不是优化这个代码。
就像建立const对象一样，程序员也可以建立volatile对象，甚至还可以建立const volatile 对象。 这个对象不能被程序员改变，但可通过外面的工具改变。

**例1: 关键字volatile有什么含义？并给出3个不同的例子。**

一个定义为volatile的变量是说这变量可能会被意想不到地改变，这样，编译器就不会去假设这个变量的值了。精确地说就是，优化器在用到这个变量时必须每次都小心地重新读取这个变量的值，而不是使用保存在寄存器里的备份。

下面是volatile变量的几个例子：

1. 并行设备的硬件寄存器（如状态寄存器）
2. 一个中断服务子程序中会访问到的非自动变量(Non-automatic varbliaes)。
3. 多线程应用中被几个任务共享的变量。

**例2: 一个参数可以既是const又是volatile吗？一个指针可以是volatile吗？解释为什么。**

第一个问题：可以。一个例子就是只读的状态寄存器。它是volatile，因为它可能被意想不到地改变；它又是const, 因为程序不应该试图去修改

第二个问题: 可以。 尽管这并不很常见。一个例子是当一个中断服务子程序修改一个指向一个buffer的指针时。

**例3: 下面的函数有什么错误？**

```cpp
int square(volatile int *ptr) {
    return *ptr * *ptr;
}
```

这段代码的目的是用来返还指针`*ptr`指向值的平方，但是，由于`*ptr`指向一个volatlie型参数，编译器将产生类似下面的代码：

```cpp
int square(volatile int *ptr) {
    int a, b;
    a = *ptr;
    b = *ptr;
    return a * b;
}
```

由于`*ptr`的值可能被意想不到地改变，因此a和b可能是不同的。 结果，这段代码可能无法返回你所期望的平方值。

正确的代码如下:

```cpp
int square(volatile int *ptr) {
    int a = *ptr;
    return a * a;
}
```

### static

- 函数体内static变量的作用范围为该函数体，不同于auto变量，该变量的内存只被分配一次，因此其值在下次调用时仍维持上次的值。
- 在模块内的static全局变量可以被模块内所有函数访问，但**不能被模块外其他函数访问**。
- 在模块内的static函数只可被这模块内的其他函数调用，这个函数的使用范围被限制在声明它的模块内。
- 在类中的static成员变量属于整个类所拥有，对类的所有对象只有一份复制
- 在类中的static成员函数属于整个类所拥有，这个函数不接收this指针，因而只能访问类的static成员变量。