

const 的一件奇妙事情是，它允许你指定一个语义约束（也就是指定一个“不该被改动”的对象），而编译器会强制实施这项约束。

它允许你告诉编译器和其他程序员某值应该保持不变。

只要这（某值保持不变）是事实，你就该确实说出来，因为说出来可以获得编译器的襄助，确保这条约束不被违反。


-----------------

STL迭代器系以指针为根据塑模出来，所以迭代器的作用就像个`T*`指针。

声明迭代器为const就像声明指针为const一样（即声明一个`T*const`指针），表示这个迭代器不得指向不同的东西，但它所指的东西的值是可以改动的。

如果你希望迭代器所指的东西不可被改动（即希望STL模拟一个`const T*`指针），你需要的是const_iterator：

```C++
vector<int> vec;
const vector<int>::iterator iter;
*iter = 10;
++iter;  // 错误，const vector<int>::iterator 的作用相当于 T * const

vector<int>::const_iterator citer;
*citer = 10;  // 错误 vector<int>::const_iterator 的作用相当于 const T *
++citer;
```

---------------------

令函数返回一个常量值，往往可以降低因客户错误而造成的意外，而又不至于放弃安全性和高效性。

举个例子，考虑有理数的`operator*`声明式：

```C++
class Rational { ... };
const Rational operator* (const Rational &lhs, const Rational &rhs);
```

许多程序员第一次看到这个声明时不免斜着眼睛说，唔，为什么返回一个const对象？

原因是如果不这样客户就能实现这样的暴行：

```C++
Rational a, b, c;
...
(a * b) = c;  // 在 a * b 的成果上调用 opreator=
```

我不知道为什么会有人想对两个数值的乘积再做一次赋值（assignment），但我知道许多程序员会在无意识中那么做，只因为单纯的打字错误（以及一个可被隐式转换为bool的类型）：

```C++
if ( a * b = c)  ... // 其实是想做一个比较(comparison) 动作
```

如果a和b都是内置类型，这样的代码直截了当就是不合法。

而一个“良好的用户自定义类型”的特征是它们避免无端地与内置类型不兼容（见条款 18），因此允许对两值乘积做赋值动作也就没什么意思了。

将 `operator*`的回传值声明为const可以预防那个“没意思的赋值动作”，这就是该那么做的原因。


--------------------

```C++
class TextBlock {
public:
    size_t length() const {
        if (!lengthIsVaild) {
            textLength = strlen(pText);  // 错误，在const 函数内不允许改变成员函数的值， static 除外
            lengthIsVaild = true;
        }
        return textLength;
    }
private:
    char* pText;
    size_t textLength;
    bool lengthIsVaild;
};
```

这两笔数据被修改对const CTextBlock对象而言虽然可接受，但编译器不同意。

解决办法很简单：利用C++的一个与const相关的摆动场：mutable（可变的）。

mutable释放掉non-static成员变量的bitwise constness约束：

```C++
mutable textLength = strlen(pText);
mutable lengthIsVaild = true;
```

---------------------------

**运用const成员函数实现出其non-const孪生兄弟**

```C++
class TextBlock {
public:
    char& operator[](size_t position) const {
        // ...
        // ... 
        // ...
        return pText[position];
    }

    char& operator[](size_t position) {
        return const_cast<char &>(
                    static_cast<const TextBlock&>(*this)
            [position]
        );
    }
private:
    char* pText;
};
```

如你所见，这份代码有两个转型动作，而不是一个。

我们打算让 `non-const operator[]`调用其 const 兄弟，但 `non-const operator[]`内部若只是单纯调用`operator[]`，会递归调用自己。

那会大概……唔……进行一百万次。

为了避免无穷递归，我们必须明确指出调用的是`const operator[]`，但C++缺乏直接的语法可以那么做。

因此这里将`*this` 从其原始类型`TextBlock&`转型为 `const TextBlock&`。

是的，我们使用转型操作为它加上const！

所以这里共有两次转型：第一次用来为`*this`添加 const（这使接下来调用 `operator[]`时得以调用const版本），第二次则是从`const operator[]`的返回值中移除const。

添加 const的那一次转型强迫进行了一次安全转型（将 non-const对象转为const 对象），所以我们使用 static_cast。

移除 const 的那个动作只可以藉由const_cast完成，没有其他选择（就技术而言其实是有的；一个C-style转型也行得通）。

至于其他动作，由于本例调用的是操作符，所以语法有一点点奇特，恐怕无法赢得选美大赛，但却有我们渴望的“避免代码重复”效果，因为它运用 `const operator[]` 实现出 non-const版本。

为了到达那个目标而写出如此难看的语法是否值得，只有你能决定，但“运用const成员函数实现出其non-const孪生兄弟”的技术是值得了解的。

更值得了解的是，反向做法——令 const版本调用 non-const 版本以避免重复——并不是你该做的事。

记住，const成员函数承诺绝不改变其对象的逻辑状态（logical state），non-const成员函数却没有这般承诺。

如果在const函数内调用non-const函数，就是冒了这样的风险：你曾经承诺不改动的那个对象被改动了。

这就是为什么“const成员函数调用non-const成员函数”是一种错误行为：因为对象有可能因此被改动。

实际上若要令这样的代码通过编译，你必须使用一个const_cast将`*this`身上的const性质解放掉，这是乌云罩顶的清晰前兆。

反向调用（也就是我们先前使用的那个）才是安全的：non-const成员函数本来就可以对其对象做任何动作，所以在其中调用一个 const 成员函数并不会带来风险。这就是为什么本例以static_cast作用于`*this`的原因：这里并不存在const相关危险。


**公众号:** *cpp_yang*

**个人微信:** *yangxg_cxy*

**今日头条:** *程序员杨小哥*

**B站:** *https://space.bilibili.com/473029051*

**知乎:** *https://www.zhihu.com/people/cpp_yang*

  
  
