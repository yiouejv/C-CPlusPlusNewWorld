

# 转换函数

```cpp
class Fraction
{
public:
    Fraction(int num, int den = 1) : m_numberator(num), m_denominator(den) {}
    operator double() const {
        return (double)(m_numberator) / m_denominator;
    }
private:
    int m_numberator;  // 分子
    int m_denominator;  // 分母
};

int main(int argc, char const *argv[])
{
    Fraction f(3, 5);
    double d = 4 + f;  // 调用operator double() 将f转为0.6
    return 0;
}
```

其中

```cpp
operator double() const {
    return (double)(m_numberator) / m_denominator;
} 
```

`operator double()` 为转换函数，返回值不用写，就是 `double`, `const` 应该要写，函数内没有改变数据。


`double d = 4 + f;` 编译器先找有没有全局的`operator +` 函数，并且第一个参数为 `int/float`, 第二个参数为`Fraction`，如果没有，则找一下`Fraction`有没有可以转换为`double`的转换函数。





