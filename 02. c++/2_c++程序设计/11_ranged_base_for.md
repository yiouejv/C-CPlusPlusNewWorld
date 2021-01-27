
```cpp
for ( decl: coll) {
    statment
}
```

`decl` 是一个类型，`coll`是一个容器，编译器会把容器内的元素一个个赋值给 `decl`。

```cpp
for (int i : {1, 3, 5, 6, 7, 9}) {
    cout << i << endl;
}
```

注意传值和传引用。

```cpp
vector<double> vec;
//...
// pass by value
for (auto elem: vec) {
    cout << elem << endl;
}

// pass by reference
for (auto& elem: vec) {
    elem *= 3;
}
```



