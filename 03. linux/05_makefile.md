make

是linux自带的构建器, 构建的规则在makefile中

---------------------------------------------

makefile 的命名:

- makefile
- Makefile

makefile 中的规则

gcc a.c b.c -o app

- 三部分: 目标，依赖。命令

    ```
    目标: 依赖
    (tab) 命令

    app:a.c b.c
        gcc a.c b.c -o app
    ```

    缺点：修改了其中一个源码文件，其他的文件也会被跟着被编译，效率低

- 第二个版本:

```makefile
app:main.c,a.c
    gcc main.o add.o -o app

main.o:mian.c
    gcc main.c -c

a.o:a.c
    gcc a.c -c
```

工作原理: 检查依赖是否存在，依赖不存在，向下搜索下边的规则，如果有规则是来生成相应的依赖的，执行规则中的命令；如果依赖存在，根据文件的更新时间， 判断是否需要更新, 如: 目标的时间一定会比依赖的文件时间晚，反之则依赖更新了，目标则需要被更新

缺点: 太冗余

- 第三个版本

自定义变量：obj=a.o, b.o, c.o, 变量的取值: aa=$(obj)

makefile 自带的变量: 大写
```
CPPFLAGS
CC
```

自动变量：

```
$@: 规则中的目标
$<：规则中的第一个依赖
$^：规则中所有的依赖

这些只能在规则中的命令中使用
```

```makefile
obj = main.o a.o b.o c.o
target = app
$(target):$(obj)
    gcc $(obj) -o $(target)

%.o:%.c
    gcc -c $< -o $@
```

模式匹配: %.o:%.c

缺点：可移植性差

- 第四个版本

    - makefile 所有的函数都有返回值
    - 查找指定目录下的指定类型的文件

        - src = $(wildcard ./\*.c) 搜索当前目录下的\*.c 文件
    - 匹配替换

        - obj = $(patsubst %.c,%.o,$(src))

```makefile
src = $(wildcard ./*.c)
obj = $(patsubst %c,%o,$(src))
app:obj
    gcc $^ -o $@

%.o:%.c
    gcc -c $< -o $@
```

- 第五个版本

增加清理项目的功能，编写一个规则

clean:

```makefile
src = $(wildcard ./*.c)
obj = $(patsubst %c,%o,$(src))
app:obj
    gcc $^ -o $@

%.o:%.c
    gcc -c $< -o $@

hello:
    echo "hello, makefile"

.PHONY:clean
clean:
    -rm $(obj) -f
```

`-rm $(obj)` 减号代表当前命令执行失败了，继续执行下面的命令

如果当前目录下恰好有一个clean文件，则clean就不会工作了，因为clean一定是最新的，因为当前的clean没有依赖，解决方案是：

声明伪目标: 不会做依赖和文件更新检查, `.PHONY`
