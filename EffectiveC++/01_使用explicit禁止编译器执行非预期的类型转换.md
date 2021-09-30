
```c++
class A {
public:
    A();    // default ctor
};

class B {
public:
    explicit B(int x = 0, bool b = true); // default ctor
};

class C {
public:
    explicit C(int x);  // not default ctor
};
```

所谓 default 构造函数是一个可被调用而不带任何实参者。

这样的构造函数要不没有参数，要不就是每个参数都有缺省值。

上述的classes B和 C的构造函数都被声明为explicit，这可阻止它们被用来执行隐式类型转换（implicit type conversions），但它们仍可被用来进行显式类型转换（explicit type conversions）


```C++
void doSomething(B object);  // 函数，接受一个类型为B的对象

B obj1;
doSomething(obj1);  // 没问题，传递一个B给doSomething 函数

B obj2(28);  // 没问题，根据28创建一个B

doSomething(28);  // 错误，doSomething 应该接受一个B
                 // 不是一个int, 而int至B之间没有隐式转换

doSomething(B(28));  // 没问题，使用B构造函数将int显示转换
```

被声明为 explicit的构造函数通常比其non-explici兄弟更受欢迎，因为它们禁止编译器执行非预期（往往也不被期望）的类型转换。除非我有一个好理由允许构造函数被用于隐式类型转换，否则我会把它声明为 explicit。


**公众号:** *cpp_yang*

**个人微信:** *yangxg_cxy*

**今日头条:** *程序员杨小哥*

**B站:** *https://space.bilibili.com/473029051*

**知乎:** *https://www.zhihu.com/people/cpp_yang*

  
  