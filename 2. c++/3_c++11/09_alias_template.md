

`alias template`  alias 别名

```cpp
template<typename T>
using Vec = std::vector<T, MyAlloc<T>>;  // standard vector using own allocator
```

我把标准模板库的`vector`的分配器改成了自己的`MyAlloc`, 下次我用 `Vec` 就代表了 `std::vector<T, MyAlloc<T>>`

```cpp
Vec<int> coll;

// is equivalent to 

std::vector<int>(int, MyAlloc<int>) coll;
```

-------------------------------------------
能不能用 `#define` 达到同样的效果呢?

```cpp
#define Vec<T> template<typename T> std::vector<T, MyAlloc<T>>;

// 于是
Vec<int> coll;

// 变成了
template<int> std::vector<int, MyAlloc<int>> coll;  // 这不是我想要的
```

`#define` 只是把内容全部替换.

-------------------------------------------------

**不能对 alias template 做模板特化, 只能对本尊做模板特化**

---------------------------------------------------------------------------

 




















