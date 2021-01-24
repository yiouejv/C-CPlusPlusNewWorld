

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

