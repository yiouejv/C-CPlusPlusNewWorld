

### 例1

```cpp
#include<iostream>
using namespace std;

// 1
void print() {}

// 2
template<typename T, typename... Types>
void print(const T& firstArg, const Types&... args)
{
    cout << firstArg << " ";
    print(args...);
}

// 3
template<typename... Types>
void print(const Types&... args)
{
    cout << "void print(const Types&... args)" << endl;
}

int main(int argc, char const* argv[])
{
    print(1, 2, 3, 4, 5, 6);
    return 0;
}
```

2 和 3 都可以接受大于0个参数的调用, 但是会调用谁呢?

对于编译器来说, 2 更特殊一点, 好比模板特化, 会调用2, 最后参数为0个时, 会调用1, 3 永久不会被调用.

### 例2

模拟C 中的 `printf`

```cpp
#include<iostream>
using namespace std;

namespace test {
    void printf(const char* s) {
        while(*s) {
            if (*s == '%' && *(++s) != '%') {
                //throw("error");
                cout << "error" << endl;
            }
            cout << *(s++);
        }
    }

    template<typename T, typename... Types>
    void printf(const char* s, const T& firstArg, const Types&... args)
    {
        if (*s) {
            if (*s == '%' && *(++s) != '%') {
                cout << firstArg << " ";
                printf(++s, args...);
            }
        }
    }
}

int main(int argc, char const* argv[])
{
    int* p1 = new int;
    test::printf("%d%s%p%f%%\n", 15, "this is ace", p1, 3.1415926);
    return 0;
}
```

### 例3

```cpp
#include<iostream>
using namespace std;

int maxinum(int n) { return n; }

template<typename... Types>
int maxinum(int n, Types... args)
{
    return max(n, maxinum(args...));
}


int main(int argc, char const* argv[])
{
    int a = maxinum(1, 2, 3, 4, 5, 6);
    cout << a;
    return 0;
}
```

### 例4

递归继承

```cpp
namespace test
{
    template<typename... Values> class tuple{};

    template<typename Head, typename... Tail>
    class tuple<Head, Tail...> : private tuple<Tail...>
    {
        typedef tuple<Tail...> Inherited;
    public:
        tuple() {}
        tuple(const Head& h, const Tail&... t) : m_head(h), Inherited(t...) {}
        Head& head() { return m_head; }
        Inherited& tail() { return *this; }
    protected:
        Head m_head;
    };
}


test::tuple<int, float, char, string> t(1, 2.0, '3', "4");
cout << t.head() << endl;
cout << t.tail().head() << endl;
```

### 例5

递归复合

```cpp
template<typename... Values> class Com {};

template<typename Head, typename... Tail>
class Com<Head, Tail...>
{
    typedef Com<Tail...> Composited;
public:
    Com() {}
    Com(const Head& h, const Tail&... tails) : m_head(h), m_tail(tails...) {}
    Head& head() { return m_head; }
    Composited& tail() { return m_tail; }
private:
    Head m_head;
    Composited m_tail;
};

test::Com<int, float, string> t(1, 2, "3");
cout << t.head() << endl;
cout << t.tail().head() << endl;
cout << t.tail().tail().head() << endl;
```

### 例6

递归委托

```cpp
template<typename... Values> class Delegation {};

template<typename Head, typename... Tail>
class Delegation<Head, Tail...>
{
    typedef Delegation<Tail...> Dele;
public:
    Delegation() {}
    Delegation(const Head& h, const Tail&... tails) : m_head(h), m_tail(new Dele(tails...)) { }
    Delegation(const Delegation& rhs) { m_head = rhs.m_head; /* 具体拷贝指针内容的部分*/ }
    Delegation& operator=(const Delegation& rhs) {
        // 自我赋值
        // 删除自身
        // 拷贝
        return *this;
    }
    Head& head() { return m_head; }
    Dele& tail() { return *m_tail; }
    ~Delegation() { delete m_tail; }
private:
    Head m_head;
    Dele* m_tail;
};


test::Delegation<int, float, string> t(1, 2, "3");
cout << t.head() << endl;
cout << t.tail().head() << endl;
cout << t.tail().tail().head() << endl;
```