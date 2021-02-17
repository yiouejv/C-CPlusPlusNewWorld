

<img src="./images/deque.png">

`deque`内包含两个迭代器，`start` 和 `finish`，用来标记`deque`空间的第一个buffer和最后一个buffer的下一个地址, deque的每一段空间称为一个buffer;`deque`内包含一个`T** map`，指向每一段空间的首地址，`size_type map_size`.

```cpp
template<class T, class Alloc=alloc, size_t=BufSize=0>
class deque {
public:
    typedef T value_type;
    typedef __deque_iterator<T, T&, T*, BufSize> iterator;
protected:
    typedef pointer* map_pointer; // T**
protected:
    iterator start;
    iterator finish;
    map_pointer map;
    size_type map_size;
public:
    iterator begin() { return start; }
    iterator end() { return finish; }
    size_type size() const { return finish-start; }
    ...
};
```

每个`iterator` 包含四个指针.

- cur: 当前这段空间所指的位置
- first：当前这段空间的开头位置
- last: 当前这段空间的最后一个位置
- node: `map_pointer`, map 指向内存的某一个地址

```cpp
template<class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ref reference;
    typedef Ptr pointer;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T** map_pointer;
    typedef __deque_iterator self;

    T* cur;
    T* first;
    T* last;
    map_pointer node;
    ...
};
```

-------------------------------------------

**deque 如何模拟连续的空间**

```cpp
// class deque
reference operator[](size_type n)
{ return start[difference_type(n)]; }

reference front()
{ return *start; }

reference back()
{
    iterator tmp = finish;
    --tmp;
    return *tmp;
}

size_type size() const
{ return finish - start; }  // 迭代器相减，deque_iterator 肯定做了operator- 重载

bool empty() const
{ return finish == start; }
```

```cpp
//class deque_iterator
reference operator*() const
{ return *cur; }

pointer operator->() const
{ return &(operator*()); }

// 两个iterator之间的距离相当于
// 两个iterator之间的buffer的总长度 +
// iter  至其buffer末尾的长度 +
// x 至其buffer起头的长度
difference_type
operator-(const self& x) const
{ return difference_type(buffer_size()) * (node - x.node - 1) +
    (cur - first) + (x.last - x.cur);
}

void set_node(map_pointer new_node) {
    node = new_node;
    first = *new_node;
    last = first + difference_type(buffer_size());
}

self& operator++() {
    ++cur;
    if (cur == last) {  // 如果抵达缓冲区的尾端
        set_node(node + 1);  // 就调至下一个缓冲区
        cur = first;  // 的起点
    }
    return *this;
}

self operator++(int) {
    self tmp = *this;
    ++*this;
    return tmp;
}

self* operator--() {
    if (cur == first) {  // 如果目前在缓冲区头部
        set_node(node - 1);  // 就跳至下一个结点
        cur = last;  // 的末端
    }
    -- cur;
    return *this;
}

self operator--(int) {
    self tmp = *this;
    --*this;
    return tmp;
}

self& operator+=(difference_type n) {
    difference+type offset = n + (cur - first);
    if (offset >= 0 && offset < difference_type(buffer_size()))
        // 目标位置在同一个缓冲区
        cur += n;
    else {
        // 目标位置不在同一个缓冲区内
        difference_type node_offset = offset > 0 ? difference_type(buffer_size())
                                                : -difference_type((-offerset - 1) / buffer_size()) - 1;
        // 切换至正确的缓冲区
        set_node(node + node_offset);
        cur = first + (offset - node_offset * difference_type(buffer_size()));
    }
    return *this;
}

self operator+(difference_type n) const {
    self tmp = *this;
    return tmp += n;
}

self& operator-=(difference_type n)
{ return *this += -n; }

self operator-(difference_type n) const
{
    self tmp = *this;
    return tmp -= n;
}

reference operator[](difference_type n) const
{ return *(*this + n);

```
-----------------------------------------------------------------------


**当map容量不够时**


map 本质是一个vector，当map容量不够时，将发生二倍扩容，原来的内容将会被copy到新空间的中间部分，方便deque扩容。

