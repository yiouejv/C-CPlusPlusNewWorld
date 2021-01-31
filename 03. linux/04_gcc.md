
gcc 工作流程

- 预处理: --E

    - 宏替换
    - 头文件展开
    - 注释去掉
    - xxx.c \-> xxx.i

- 编译: --S

    - xxx.i \-\>  xxx.s
    - 生成汇编文件

- 汇编: -c

    - xxx.s \-\> xxx.o
    - 二进制文件

- 链接: xxx.o \-\> xxx （可执行文件）

--------------------------------------------

常用参数:

- `-v`: 查看版本
- `-I`: 编译时指定头文件的路径, 常用
- `-c`: 将汇编文件生成二进制文件
- `-o`: 指定生成文件名
- `-g`: gdb 调试时需要加
- `-D`: 编译时指定宏, 使用场景，测试程序时
- `-Wall`: 编译时添加警告信息
- `-On`: 优化代码，n是优化级别: 1,2,3
- `-L`: 指定静态库的路径
- `-l`: 指定静态库的名字

------------------------------------------------
静态库和动态库的制作和使用

- 库是什么？

    将源代码\-\>二进制的源代码，加密

    .c .cpp

- 库制作出来之后，如何给用户使用？

    - 头文件有定义
    - 制作出来的库

- 静态库的制作和使用

    - 命名规则: libxxx.a
    - 制作步骤:

        - 源码, .c .cpp
        - 将.c 文件生成.o
        - 将.o 打包, 使用打包工具, ar(archive) rcs 静态库的名字 源码

            `ar rcs libtest.a *.o`

    - 静态库的使用: gcc main.c -I includepath -L libpath -l xxx(libxxx.a)

- 动态库的制作和使用

    - 命名规则: libxxx.so
    - 制作步骤:

        - 将源文件生成.o: gcc 源文件 -c -fpic(fPIC)
        - 打包: gcc -shared *.o -o libxxx.so

    - 库的使用:

        - 头文件 a.h
        - 动态库 libtest.so
        - 参数函数声明编写测试程序 main.c

            gcc main.c -I includepath -L libpath -l xxx(libxxx.so)

- 解决动态库加载失败的问题

    当系统加载可执行代码的时候，能够知道所依赖库的名字，但是还需要知道绝对路径。此时就需要系统动态加载器(dynamic linker/loader), 对于elf格式的可执行文件，是由`ld-linux.so`来完成的，它先后搜索 elf 文件的 DT_RPATH 段，环境变量 LD_LIBRARY_PATH, /etc/ld.so.cache 文件列表，/lib/,/usr/lib 目录找到库文件后将其载入内存。

    - elf格式: 在gcc 下生成的可执行文件都是elf 格式的, shell: file filename
    - 如何让系统找到共享库

        - ldd 可执行文件: 查看需要的链接库
        - 拷贝自己制作的库到 /lib 或 /usr/lib
        - 环境变量:

            - 临时设置: export LD_LIBRARY_PATH=libpath:$LD_LIBRARY_PATH
            - 永久设置:

                - 用户级别: ~/.bashrc
                - 系统级别: /etc/profile
                - 在用户级别或系统级别把 LD_LIBRARY_PATH 设置进去

        - /etc/ld.so.cache 文件列表

            - 找到配置文件：/etc/ld.so.conf
            - 把动态库的绝对路径添加到文件中
            - 执行一个命令: sudo idconfig

        - 知识点扩展:

            - dlopen, dlclose, dlsym
