
什么叫 `variadic template`: <a href="../2_c++程序设计/09_variadic_templates.md">2_c++程序设计/09_variadic_templates.md</a>

---------------------------------------------------



```cpp
void print()
{}

template<class T, class... Types>
void print(const T& firstArg, const Types&... args)
{
    cout << "template<class T, class... Types>" << endl;
}

template<class... Types>
void print(const Types&... args)
{
    cout << "template<class... Types>" << endl;
}
```

上面两个`variadic template` 能不能共存？

哪个是泛化，哪个是特化？


---------------------------------------------------------------

**variadic template 应用** 

*场景一： 可以很方便的完成 recursive function call*

```cpp
class CustomerHash
{
public:
    std::size_t operator() (const Customer& c) {
        return hash_val(c.fname, c.lname, c.name, c.no);
    }
};


#include<functional>
template <typename... Types>
inline size_t hash_val(const Types&... args)
{
    size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}


template <typename T, typename... Types>
inline void hash_val(size_t& seed, const T& val, const Types&... args)
{
    hash_combine(seed, val);
    hash_val(seed, args);
}

template <typename T>
inline void hash_val(size_t& seed, constT& val)
{
    hash_combine(seed, val);
}

template <typename T>
inline void hash_combine(size_t& seed, const T& val)
{
    seed ^= std::hash<T>()(val) + 0x9e379b9 + (seed << 6) + (seed >> 2);
}
```


*场景二: 可以很方便的完成 recursive inheritance*

```cpp
#include<iostream>
#include<string>
using namespace std;

namespace test {
    template<typename... Values> class tuple;
    template<> class tuple<> {};

    template<typename Head, typename... Tail>
    class tuple<Head, Tail...> : private tuple<Tail...>
    {
        typedef tuple<Tail...> inherited;
    protected:
        Head m_head;
    public:
        tuple() {}
        tuple(Head v, Tail... vtail) : m_head(v), inherited(vtail...) {}

        auto head()->decltype(m_head) { return m_head; }
        inherited& tail() { return *this; }
    };
}

int main(int argc, char const* argv[])
{
    test::tuple<int, float, string> t(41, 6.3, "nico");
    return 0;
}
```

继承关系图如下：

<img src="../images/recursive_interitance.png">







