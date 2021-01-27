

decltype

`declare type`


defines a type equivalent to the type of an expression

定义一个类型, 等同于这个表达式的类型


-------------------------------------------------------
**1. 运用在函数返回值**

```cpp
template<typename T1, typename T2>
decltype(x+y) add(T1 x, T2 y);
```

定义了一个 `add function`, add 的返回值是什么类型呢? 我写不出来, 我让编译器去推, 返回值类型就是 `x+y`的类型, 我写成 `decltype(x+y)`, 道理上是能过的, 但是编译时是从上往下看, `x`, `y`编译器还不知道是什么东西, 编译不过.

```cpp
template<typename T1, typename T2>
auto add(T1 x, T2 y)->decltype(x+y);
```

返回值类型我写不出来, 我写一个`auto`, 后面再告诉编译器是`decltype(x+y)`, 中间要用`->`.


-------------------------------------------------------------

**2. 运用在模板里**

```cpp
template <typename T>
void test_decltype(T obj)
{
    map<string, float>::value_type elem1;

    map<string, float> coll;
    decltype(coll)::value_type elem2;  //面对obj取其class type 的inner typedef, 因为如今我们有了工具 decltype

    // 如今有了 decltype 我们可以这样
    typedef typename decltype(obj)::iterator iType;
    // 等价于
    // typedef typename T::iterator iType;
}
```

-----------------------------------------------------------------

**3. 推导lambda 的类型**

```cpp
auto cmp = [](const Person& p1, const Person& p2){
    return p1.lastname < p2.lastname;
};

std::vector<decltype(cmp)> coll;
```











