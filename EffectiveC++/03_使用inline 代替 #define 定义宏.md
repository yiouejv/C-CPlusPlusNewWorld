

宏看起来像函数，但不会招致函数调用（function call）带来的额外开销。下面这个宏夹带着宏实参，调用函数f：

```C++
// 以 a, b 的较大值调用 f
#define CALL_WITH_MAX f( (a) > (b) ? (a) : (b) )
```

这般长相的宏有着太多缺点，光是想到它们就让人痛苦不堪。

无论何时当你写出这种宏，你必须记住为宏中的所有实参加上小括号，否则某些人在表达式中调用这个宏时可能会遭遇麻烦。

但纵使你为所有实参加上小括号，看看下面不可思议的事

```C++
int a = 5, b = 0;
CALL_WITH_MAX(++a, b);		// a 被累加二次
CALL_WITH_MAX(++a, b + 10);  // a 被累加一次
```

在这里，调用f之前，a的递增次数竟然取决于“它被拿来和谁比较”！

幸运的是你不需要对这种无聊事情提供温床。

你可以获得宏带来的效率以及一般函数的所有可预料行为和类型安全性（type safety）

```C++
template<typename T>
inline void CallWithMax(const T &a, const T &b) {
						// 由于我们不知道T是什么，所以采用 pass by reference-to-const
	f(a > b ? a : b);
}
```

这个template产出一整群函数，每个函数都接受两个同型对象，并以其中较大者调用f。

这里不需要在函数本体中为参数加上括号，也不需要操心参数被核算（求值）多次……等等。此外由于callWithMax是个真正的函数，它遵守作用域（scope）和访问规则。

例如你绝对可以写出一个“class内的private inline函数”。一般而言宏无法完成此事。



**公众号:** *cpp_yang*

**个人微信:** *yangxg_cxy*

**今日头条:** *程序员杨小哥*

**B站:** *https://space.bilibili.com/473029051*

**知乎:** *https://www.zhihu.com/people/cpp_yang*

  
  