
<img src="./images/vector.png"> 

两倍成长时涉及到资源的拷贝，拷贝会调用拷贝构造函数，原对象会被销毁，销毁会调用析构函数。

连续空间一般都要提供`operator[]`。

-----------------------------------

**vector's iterator**

vector 是一个连续的容器，`navite pointer`就能做到迭代器的功能。

