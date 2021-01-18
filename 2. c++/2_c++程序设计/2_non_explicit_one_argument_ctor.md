
```cpp
class Fraction
{
public:
    Fraction(int num, int den = 1) : m_numberator(num), m_denominator(den) {}
    Fraction operator+(const Fraction& f) {
        return Fraction(...);
    }
private:
    int m_numberator;  // 分子
    int m_denominator;  // 分母
};

int main(int argc, char const *argv[])
{
    Fraction f(3, 5);
    Fraction d = f + 4;
    return 0;
}
```

`Fraction d = f + 4;` ，编译器会调用`non-explicit ctor`将4 转为`Fraction(4, 1)`, 然后调用`operator +`, 将其他类型的转换为此类型的, 和 `1_conversion_function.md` 描述的相反


------------------------------------------

```cpp
class Fraction
{
public:
    Fraction(int num, int den = 1) : m_numberator(num), m_denominator(den) {}
    operator double() const {
        return (double)m_numberator / m_denominator;
    }
    Fraction operator+(const Fraction& f) {
        return Fraction(...);
    }
private:
    int m_numberator;  // 分子
    int m_denominator;  // 分母
};

int main(int argc, char const *argv[])
{
    Fraction f(3, 5);
    Fraction d = f + 4;  // Error
    return 0;
}
```

如果`conversion function` 和 `non explicit one argument` 同时存在，编译器则不知道调用哪个，就会出错。


------------------------------
**解决办法**

```cpp
class Fraction
{
public:
    explicit Fraction(int num, int den = 1) : m_numberator(num), m_denominator(den) {}
    operator double() const {
        return (double)m_numberator / m_denominator;
    }
    Fraction operator+(const Fraction& f) {
        return Fraction(...);
    }
private:
    int m_numberator;  // 分子
    int m_denominator;  // 分母
};

int main(int argc, char const *argv[])
{
    Fraction f(3, 5);
    Fraction d = f + 4;  // Error
    return 0;
}
```

`Fraction(int num, int den = 1) : m_numberator(num), m_denominator(den) {}` 的前面加上`explicit`（明确的），告诉编译器，你不要帮我“暗度陈仓”哦。

`Fraction d = f + 4;` conversion from 'double' to 'Fraction' requested;


**explicit 用在什么地方**

1. 90% 上述这种情况。


---------------------------------------------------

**STL库中转换函数的例子**

<img src="../images/conversion_function.png">

`operator[]` 函数应该要返回`bool`型，但是却返回了一个类`__bit_reference`, `__bit_reference`应该提供一个转换成`bool`型的转换函数，正如`operator bool() const`
