

<strong>\[...\]\(...\)mutable throwSpec \-\> retType \{ ... \}</strong>

[]  可以取用外部的变量

()  参数列表

{}  函数体

mutable 可变的

throwSpec 是否抛出异常, 加不加 noexcept

`mutable throwSpec -> retType` 都可以省略.


-------------------------------------------------------

```cpp
// 例1
int id = 0;
auto f = [id]() mutable {
    cout << "id: " << id << endl;
    ++id;
};

id = 42;
f();
f();
f();
cout << "id: " << id << endl;
```


```cpp
// 例2
int id = 0;
auto f = [&id](int param) {
    cout << "id: " << id << endl;
    ++id; ++param;
};

id = 42;
f(7);
f(7);
f(7);
cout << "id: " << id << endl;
```


```cpp
// 例3
int id = 0;
auto f = [id]() {
    cout << "id: " << id << endl;
    ++id;  // Error, id is readonly
};

id = 42;
f();
f();
f();
cout << "id: " << id << endl;
```

-------------------------------------------------------
只写=表示其他所有的对象都通过传值的方式使用


```cpp
int x = 0;
int y = 42;
int z = 1;
auto qqq = [=, &z]() mutable {
    z = 100;
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "z: " << z << endl;
};  // 只写=表示其他所有的对象都通过传值的方式传进来

cout << "z: " << z << endl;
qqq();
```


