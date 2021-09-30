
`#define`不被视为语言的一部分。那正是它的问题所在。当你做出这样的事情:

```C++
#define ASPECT_RATIO 1.653
```

记号名称`ASPECT_RATIO`也许从未被编译器看见；

也许在编译器开始处理源码之前它就被预处理器移走了。

于是记号名称 ASPECT_RATIO 有可能没进入记号表（symbol table）内。

于是当你运用此常量但获得一个编译错误信息时，可能会带来困惑，因为这个错误信息也许会提到 1.653 而不是 ASPECT_RATIO。

如果 ASPECT_RATIO 被定义在一个非你所写的头文件内，你肯定对1.653以及它来自何处毫无概念，于是你将因为追踪它而浪费时间。

这个问题也可能出现在记号式调试器（symbolic debugger）中，原因相同：你所使用的名称可能并未进入记号表（symbol table）。

解决之道是以一个常量替换上述的宏（#define）：

```C++
const double aspectRatio = 1.653;  // 大写名称通常用于宏，因此这里改变变量名称写法
```

----------------------------

当我们以常量替换 `#define`，有两种特殊情况值得说说。

第一是定义常量指针（constant pointers）。

由于常量定义式通常被放在头文件内（以便被不同的源码含入），因此有必要将指针（而不只是指针所指之物）声明为const。

例如若要在头文件内定义一个常量的（不变的）`char *based`字符串，你必须写const两次：

```C++
const char * const authorName = "yang";
```

第二个值得注意的是class专属常量。

为了将常量的作用域（scope）限制于class内，你必须让它成为class的一个成员（member）；

而为确保此常量至多只有一份实体，你必须让它成为一个static成员：

```C++
class GamePlayer {
private:
    static const int numTurns = 5;
};
```


**公众号:** *cpp_yang*

**个人微信:** *yangxg_cxy*

**今日头条:** *程序员杨小哥*

**B站:** *https://space.bilibili.com/473029051*

**知乎:** *https://www.zhihu.com/people/cpp_yang*

  
  