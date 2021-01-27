

auto: 编译器自动帮我们推导变量的类型

```cpp
string target;
list<string> c;
//...
list<string>::iterator ite;
ite = find(c.begin(), c.end(), target);
```

完整的 `ite` 的类型为 `list<string>::iterator`

```cpp
string target;
list<string> c;
//...
auto ite = find(c.begin(), c.end(), target);
```

auto 自动帮我们推导，编译器可以通过`find`的返回值类型推导出`ite`的类型。

**注意: auto 一定要让编译器能够推导，不然编译不过**

```cpp
string target;
list<string> c;
//...
auto ite;
ite = find(c.begin(), c.end(), target);
```

这种情况就不行，编译器无法推出`ite`是什么类型。


