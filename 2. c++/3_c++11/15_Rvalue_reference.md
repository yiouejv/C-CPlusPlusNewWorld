

右值引用，出现的意义是为了要解决非必要的拷贝

When the right-hand side of an assignment is an rvalue, then the left-hand side object can steal resources from the right-hand side object rather than performing a separate allocation, thus enabling move semantics

Lvalue: 可以出现于 operator= 左侧者
Rvalue: 只能出现于 operator= 右侧者

```cpp
int a = 9;
int b = 4;
a = b;  // ok
b = a;  // ok
a = a + b;  // ok
a + b = 42;  // Error 
```

```cpp
string s1("hello");
string s2("world");
s1 + s2 = s2;  // 竟然能通过编译
cout << "s1: " << s1 << endl;  // s1: hello
cout << "s2: " << s2 << endl;  // s2: world
string() = "world";   // 竟然可以对 temp obj 赋值
```

```cpp
complex<int> c1(3, 8), c2(1, 0);
c1 + c2 = complex<int>(4, 9);  // c1 + c2 可以当作Lvalue吗
cout << "c1: " << c1 << endl;  // c1: (3,8)
cout << "c2: " << c2 << endl;  // c2: (1, 0)
complex<int>() = complex<int>(4, 9);   // 竟然可以对temp object 赋值
```

临时对象就是一种右值，右值不可以放在左边。

上述`string` `complex` 可以是c++自己没有遵循这个原则。

------------------------------------------------------
```cpp
int foo() { return 5; }
int x = foo();  // ok
int* p = &foo();  // 对着Rvalue 取其reference 不可以。
foo() = 7;
```

函数的返回值是一个右值，对右值取地址是不可以的。

现在c++给我们一个新的语法，可以对 Rvalue reference

当Rvalue 出现于 `operator=(copy assignment)` 的右侧，我们认为对其资源进行偷取/搬移(move)而非拷贝是可以的，是合理的。

1. 必须有语法让我们在**调用端**告诉编译器，这个是Rvalue
2. 必须有语法让我们在**被调用端**写出一个专门处理Rvalue的所谓的`move assignment`函数

-----------------------------------------------------
```cpp
class A
{
public:
    A() {}
    void test(string &str) {
        cout << "string &str: " << str << endl;
    }
    void test(string &&str) {
        cout << "string &&str: " << str << endl;
    }
};

A a;
string s("hello");
a.test(s);
a.test(string("world"));
```

`&&` 修饰的表示是一个右值，传参数传递的是一个右值时，就会调用右值那个函数。

----------------------------------------------------------

`copy ctor`原理是深拷贝，指针指向的内容再copy一份。

<img src="../images/deep_copy.png">

`move`原理的新的指针指向原来的内存块，把老指针的指向给断了。

<img src="../images/move_copy.png">

此时只有一个指针指向那一块内存，老指针就不能再用了。 显然临时对象就很符合这种操作，相当于被“偷”掉了。


另外一种情况，左值不打算用了，想把它当作右值去使用，`std::move(lvalue)`, 必须确保后续不再使用了。


------------------------------------------------------

**unperfect forwarding**

```cpp
void process(int& i) { cout << "process(int&): " << i << endl; }
void process(int&& i) { cout << "process(int&&): " << i << endl; }
void forward(int&& i) { cout << "forward(int&&): " << i << endl; process(i); }

int a = 0;
process(a);  // 变量被视为左值
process(1);  // temp obj 被视为右值
process(std::move(a));  // 强制将a由左值改为右值
forward(2);  // 右值经由forward()传给另外一个函数却变成了左值，原因是传递过程中它变成了一个 name object
forward(std::move(a));
```

标准库提供了完美的forward, 用`std::forward`即可

----------------------------------------------------------------
**写一个 move aware class**

```cpp
namespace test
{
class string
{
public:
    string() {}
    ~string() { if (m_data) delete m_data; }
    string(const char* str) : _len(strlen(str)) {
        m_data = new char[_len + 1];
        if (str) {
            strcpy(m_data, str);
        }
        else {
            *m_data = '\0';
        }
    }

    string(const string& rhs) : _len(rhs.size()) {
        m_data = new char[_len + 1];
        strcpy(m_data, rhs.m_data);
    }

    string(string&& rhs) noexcept : _len(rhs.size()), m_data(rhs.m_data) {
        rhs._len = 0;
        rhs.m_data = nullptr;
    }

    string& operator=(const string& rhs) {
        if (m_data != rhs.m_data)
        {
            if (m_data) delete m_data;
            _len = rhs.size();
            m_data = new char[_len + 1];
            strcpy(m_data, rhs.m_data);
        }
        return *this;
    }

    string& operator=(string&& rhs) noexcept {
        if (m_data != rhs.m_data)
        {
            if (m_data) delete m_data;
            _len = rhs.size();
            m_data = rhs.m_data;
            rhs._len = 0;
            rhs.m_data = nullptr;
        }
        return *this;
    }


    int size() const { return _len; }
private:
    char* m_data;
    int _len;
};

}


test::string a;
string aa;
test::string b("hello world");
test::string c(b);
test::string d;
d = a = b;
test::string e(move(a));
```

`move ctor`, `move operator=` 要加上`noexcept`, 

当容器内空间不够, 发生`move`行为时, 如果类中的 `move`函数没有加`noexcept`, 容器则不会使用它.



