
一个类创建出来像一个指针

### 关于智能指针

```cpp
template<class T>
class shared_ptr
{
public:
	shared_ptr(T* p) : px(p) {}
	T& operator*() const {
		return *px;
	}
	T* operator->() const {
		return px;
	}

private:
	T* px;

};

struct Foo
{
	...
	void method(void) {}
};

int main(int argc, char const *argv[])
{
	shared_ptr<Foo> sp(new Foo);
	Foo f(*sp);  // 等价于 *px;
	sp->method();  // 等价于 px->method();
	return 0;
}
```


### 关于迭代器 （另外一种智能指针）

一般的智能指针不需要写`++`, `--`运算符，但是作为迭代器则需要。

```cpp
template <class T>
struct __list_node {
	void* prev;
	void* next;
	T data;
};

template<class T, class Ref, class Ptr>
struct __list_iterator {
	typedef __list_iterator<T, Ref, Ptr> self;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef __list_node<T>* link_type;
	link_type node;
	bool operator==(const self& x) const { return node == x.node; }
	bool operator!=(const self& x) const { return node != x.node; }
	reference operator*() const { return (*node).data; }
	pointer operator->() const { return &(operator*()); }
	self& operator++() { node = (link_type)((*node).next); return *this; }
	self operator++(int) { self tmp = *this, ++*this, return tmp; }
	self& operator--() { node = (link_type)((*node).prev); return *this}
	self operator--(int) { self tmp = *this, --*this, return tmp; }
};

int main(int argc, char const *argv[])
{
	list<Foo>::iterator ite;
	...
	*ite;  // Foo obejct
	ite->method();  // Foo->method();
	// 意思是调用 Foo::method();
	// 相当于: (*ite).method();
	// 相当于: &((*node).data)->method();
	return 0;
}
```