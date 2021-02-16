
泛型编程（Generic Programing）的思想和面向对象编程（object-oriented Programming）的思想是相反的。

OOP是把数据和操作数据的函数组成一个类，通过对象调用，而GP是把数据和操作数据的函数分开，数据放在容器内（Container）, 操作数据的函数也就是算法（Algorithm）, 迭代器（Iterator）启到中间桥梁的作用，连接容器和算法。

迭代器相当于一个指针，有`class iterator` 和 `non-class iterator`

迭代器会提供5中定义，`#typedef`, 分别是

- `value_type`
- `diffrence_type`
- `iterator_category`
- `pointer`
- `reference`

算法中会使用这五种定义。


萃取机(Iterator Traits)用以分辨所获得的迭代器是 `class iterator` 或者 `native pointer to T`, 利用偏特化(partial specialization)可以达到目标

```cpp
template<typename I>
struct iterator_traits {
    typedef typename I::value_type value_type;
};

// 两个partial specialization
template<typename T>
struct iterator_traits<T*> {
    typedef T value_type;
};

template<typename T>
struct iterator_traits<const T*> {
    typedef T value_type;
};

// 于是当需要知道I的value_type 时便可以这么写
template<typename I, ...>
void algorithm(...) {
    typename iterator_traits<I>::value_type v1;
}
```

