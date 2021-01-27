

function like classes 所谓仿函数

```cpp
template <class T>
struct identity : public unary_function<T, T> {
	const T&;
	operator() (const T& x) const { return x; }
};

template <class T1, class T2>
struct pair {
	T1 first;
	T2 second;
	pair() : first(T1()), second(T2()) {}
	pair(const T1& a, const T2& b) : first(a), second(b) {}
	... 
};

template <class Pair>
struct select1st : public unary_function<Pair, typename Pair::first_type> {
	const typename Pair::first_type&;
	operator() (const Pair& x) const
	{ return x.first; }
};

template <class Pair>
struct select2nd : public unary_function<Pair, typename Pair::second_type> {
	const typename Pair::second_type&;
	operator() (const Pair& x) const
	{ return x.second; }
};
```

c++ 的标准库中，包含了一些仿函数，重载了操作符(), `operator()`, 继承了一些没有成员的类，如`unary_function`, `binary_function`。

```cpp
template <class Arg, class Result>
struct unary_function {
	typedef Arg argument_type;
	typedef Result result_type;
};

template <class Arg1, class Arg2, class Result>
struct binary_function {
	typedef Arg1 first_argument_type;
	typedef Arg2 second_argument_type;
	typedef Result result_type;
};
```

