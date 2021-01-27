
场景一： 多个部门之间，多个组之间开发程序，可能沟通不及时，大家的命名有可能重复，所以需要一个namespace。

场景二： 我可能在测试程序的时候，不愿开很多项目，测试函数可能一样，可能需要一个namespace

```cpp
#include<iostream>
using namespace std;

namespace jj01
{
    void test() {
        cout << "test1" << endl;
    }
} // namespace

namespace jj02
{
    void test() {
        cout << "test2" << endl;
    }
} // namespace

int main(int argc, char const *argv[])
{
    jj01::test();
    jj02::test();
    return 0;
}
```


