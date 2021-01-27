

Before C++11, programmers, expecially novices, could easily become confused by the question of how to initialize a variable or an obejct. Initialization could happen with parenthese, braces, and/or assignment operators.

For this reason, C++11 introduced the concept of **uniform initilization**, which means that for any initilization, you can use **common syntax**. This syntax uses **braces**, so the following is possible now:

```cpp
int values[] {1, 2, 3};
vector<int> v{2, 3, 5, 7, 9};
vector<string> cities {
    "Berlin", "New York", "London"
};
complex<double> c{4.0, 3.0}; // equivalent to c(4.0, 3.0)
```


原来我们可能要这么写

```cpp
Rect r1 = {3, 5, 2, 2};
Rect r1(2, 3, 5, 6);
int ia[6] = {27, 210, 22, 12};
```

其实是利用一个事实，编译器看到 `{t1, t2, t3, ...}`, 便做出一个 `initializer_list<T>`,它关联一个`array<T, n>`。 调用函数（例如ctor）时该`array` 内的元素可被编译器分解逐一传给函数。 

但若函数参数是个`initializer_list<T>`, 调用者却不能给予数个T参数然后以为它们会被自动转为一个`initializer_list<T>` 传入


