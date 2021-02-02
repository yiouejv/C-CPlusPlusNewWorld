
gcc -g

编译器会保留函数名和变量名，否则只有地址。

启动gdb:

    - gdb 可执行程序的名字
    - 往程序传参, 在gdb模式下: set args xxx xxx
    - l: 查看文件内容，默认显示main函数文件的代码, 默认10行

    - 查看源代码:

        - `list showsize`
        - `set listsize n`
        - `l 5`: 显示第5行的上面一部分，下面一部分
        - `l function`:  显示函数的上下文信息
        - `l filename:5`:  显示该文件的第5行的上下文
        - `l filename:function`: 显示该文件的function函数的上下文
    - 断点设置:

        - 设置断点: break 行号, 简写: b 行号

            - b 函数名
            - b 文件名:行号
            - b 文件名:函数名

        - 查看断点: info break, 简写 i b
        - 删除断点: delete 断点编号, 简写: d 编号
        - 删除多个断点：d 4-7 删除4-7之前的断点；d 4 7 删除 4 7 两个断点
        - dis 编号：设置断点不可用, disable
        - ena 编号: 设置断点可用, enable
        - 设置条件断点: b 行号 if 变量=一个值

    - 调试相关命令:

        - run: r, 停在第一个断点的位置
        - start: 运行，停在main函数的第一行
        - print i: p i
        - ptype i: 打印类型
        - 向下单步调试:

            - next: 向下单步调试, 遇到函数不会进入函数体
            - step: 进入函数体的内部
            - finish: 跳出函数体, 看以下函数体中的循环是否有断点，如果有删掉，或设置无效

        - 继续运行gdb，停在下一个断点的位置

            - continue: c

        - display i: 每执行一行代码，都显示i的值, 变量自动显示
        - undisplay 编号: 取消自动显示
        - info display: 查看编号
        - 直接设置变量等于某一个值, 相当于程序执行到了当前的状态: set var i=5
        - until: 从循环体中直接跳出，如果打了断点则会跳出失败
        - quit: 退出

