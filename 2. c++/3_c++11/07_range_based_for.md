
参考: <a href="../2_c++程序设计/11_ranged_base_for.md">2_c++程序设计/11_ranged_base_for.md</a>

```cpp
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class C
{
public:
    C(const string& str) : s(str) { }
    string get_str() const { return s; }
private:
    string s;
};


int main(int argc, char const* argv[])
{
    vector<string> v{"hello", "world"};
    for (const C& c : v) cout << c.get_str() << endl;
    return 0;
}
```

这里利用了`non-explicit one argument ctor` 实现了自动转换。 

`for (const C& c : v) cout << c.get_str() << endl;` 注意`for` 中的 `const` 不能少，临时变量不能作为非`const`的引用参数。

如果`C(const string& str) : s(str) { }` 前加上`explicit`修饰就不能实现自动转换；





