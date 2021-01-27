
### 类模板

```cpp
template <typename T>
class Complex
{
public:
    Complex(const T& r = 0, const T& i = 0) : re(r), im(i) {}
    T& real() const {return re;}
    T& imag() const {return im;}
private:
    T re, im;
};


int main(int argc, char const *argv[])
{
    
    Complex<double> c1(2, 1.5);
    Complex<int> c2(1, 2);
    return 0;
}
```


### 函数模板

```cpp
template <class T>
inline const T&
_min(const T& x, const T& y)
{
    return x < y ? x : y;
}

class stone
{
public:
    stone() {}
    stone(const int w, const int h, const int weight = 10)
        : _w(w), _h(h), _weight(weight) {}

    bool operator<(const stone& rhs) const
    {
        return _weight < rhs._weight;
    }

private:
    int _w, _h, _weight;
};


int main(int argc, char const* argv[])
{
    stone r1(2, 3), r2(3, 3), r3;
    r3 = _min(r1, r2);
    return 0;
}
```

### 成员模板

```cpp
class Base1 {};  // 鱼类
class Derived1 : public Base1 {};  // 鲫鱼

class Base2 {};  // 鸟类
class Derived2 : public Base2 {};  // 麻雀

Template<typename T1, typename T2>
struct pair
{
	T1 first;
	T2 second;
	pair() : first(T1()), second(T2()) {}
	pair(const T1& a, const T2& b) : first(a), second(b) {}

	template<typename U1, typename U2>
	pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
};

int main(int argc, char const *argv[])
{
	pair<Base1, Base2>(pair<Derived1, Derived2>());
	return 0;
}
```

`pair<Base1, Base2>(pair<Derived1, Derived2>());` 我能不能用<鲫鱼, 麻雀> 赋值给 <鱼类，鸟类>, 显然是可以的，相反则不行。

```cpp
template<typename U1, typename U2>
pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
```

这种在模板类里面的模板，叫成员模板。 

标准库中大量的类构造函数有应用，使得构造函数更有弹性。
