

**类型别名**


```cpp
typedef void(*func)(int, int);
```

这里定义了一个`func` 是一个函数指针, 函数的参数为 (int, int), 初学者很难看出 `func`这是一个什么东西.

改成下面这样就很明显的可以看出来了

```cpp
using func = void(*)(int, int);  // (*) 括号不能省略

void example(int, int) {}
func f = example;  // func 的类型是一个函数指针, 定义了一个变量f, 初始化为example;
```

---------------------------------------------------------------

**using 可能出现的场景**

1. 打开命名空间

```cpp
using namespace std;  // 打开std 空间
using std::count;  // 打开空间里的某一个
```

2. 在类内告诉编译器某个变量或类型在哪里定义.

3. `type alias, alias template`













