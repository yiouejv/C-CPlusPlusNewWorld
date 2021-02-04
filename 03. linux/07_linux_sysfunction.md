
K 查看函数文档

### open

依赖头文件

```cpp
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
```

函数原型:

- int open(const char\* pathname, int flags)
- int open(const char\* pathname, int flags, mode\_t mode);

参数:

- flags:
    
    - 必选项: O\_RDONLY, O\_WRONLY, O\_RDWR
    - 可选项:

        - 创建文件: O_CREAT
            
            - 创建文件时检测文件是否存在 O_EXCL
            - 如果文件存在，返回-1
            - 必须与O_CREAT 一起使用

        - 追加文件：O_APPEDN
        - 文件截断: O_TRUNC (相当于文件清空)
        - 设置非阻塞: O_NONBLOCK
    
    - mode: 指定文件的权限, 八进制数

        - mode = mode & ~umask

### close

```c
#include<unistd.h>
```

int close(int fd)

关闭文件

### read

- ssize\_t read(int fd, void\* buf, size\_t count);

    - 参数:

        - fd: open的返回值
        - buf: 缓冲区，存储要读取的数据
        - count：缓冲区能存储的最大字节数 sizeof(buf)
        - size\_t: unsigned int
        - ssize\_t: signed\_int

    - 返回值:

        - -1: 失败
        - \>0: 读出的字节数
        - =0: 文件读完了

### write

- ssize\_t write(int fd, const void\* buf, size\_t count);

    - 参数:

        - fd
        - buf: 要写到文件的数据
        - count: strlen(buf)
    
    - 返回值:

        - -1: 失败
        - \>0: 写入到文件的字节数

### 练习

有一个很大的文件，open，读出数据，写到另外一个文件中, 参考: <a href="code/copy.cpp">code/copy.cpp</a>


### perror

perror(const char\* s)

首先会打印 `*s` 指向的字符串，然后再根据`errorno`打印出具体的错误信息, 系统函数调用失败了会自动设置全局变量 `errorno`的值

### lseek

`off_t lseek(int fd, off_t offset, int whence)`

参数:

- fd
- offset
- whence: `SEEK_SET`, `SEEK_CUR`, `SEEK_END`, 头部，当前，尾部

文件指针移动到头部: `lseek(fd, 0, SEEK_SET)`   
获取指针当前位置: `int len = lseek(fd, 0, SEEK_CUR)`  
获取文件长度: `int len = lseek(fd, 0, SEEK_END)`  
文件扩展: 文件原大小为100k, 扩展为1100k, `lseek(fd, 1000, SEEK_END)`, 最后做一次写操作 `write(fd, "", 1);`   

### 阻塞和非阻塞

阻塞和非阻塞是文件的属性还是read函数的属性？

- 文件的属性
- 普通文件: 默认不阻塞
- 终端设备: 默认阻塞，/dev/tty 代表当前的终端，管道，套接字默认阻塞

-------------------------------------------------------------------------

### stat

man 查看详情

判断权限: `st_mode & 二进制数`

### lstat

和 stat 的区别，在访问链接文件上, lstat 读取的链接文件本身的属性，stat读取的是链接文件指向的文件属性

### access 

检测当前用户指定文件是否具有某种属性

- 当前用户, 使用哪个用户调用这个函数，这个用户就是当前用户
- `int access(const char* pathname, int mode);`
    
    - pathname: 文件名
    - mode: 4种权限，`R_OK, W_OK, X_OK, F_OK 文件是否存在`
    - 返回值: 0 有权限，-1没有权限

### chmod

`int chmod(const char* filename, int mode);`

- mode: 文件权限，八进制数

### chown

`int chown(const char* path, uid_t owner, gid_t group);`

- path: 文件路径
- owner: 整型值，用户id， /etc/passwd
- group: 组id，/etc/group

### truncate

修改文件大小

`int truncate(const char* path, off_t length)`

- path: 文件名
- length: 文件的最终大小

### rename

`int rename(const char* oldpath, const char* newpath);`

### chdir

修改当前进程的路径, `int chdir(const char* path);`

### getcwd

获取当前进程的工作目录，`char* getpwd(char* buf, size_t size);`

- buf：缓冲区，存储当前的工作目录
- size: 缓冲区大小

### mkdir

`int mkdir(const char* pathname, mode_t mode);`

- pathname: 创建的目录名
- mode: 目录权限，` mode & ~umask`

### rmdir

删除一个空目录

`int rmdir(const char* pathname);`

-------------------------------------------------

目录遍历相关函数

- 打开一个目录: `DIR* opendir(const char* name);`

    - 参数: 目录名
    - 返回值: 指向目录的指针

- 读目录:

`struct dirent* readdir(DIR *dirp);`

    - 参数：opendir 的返回值
    - 返回值：目录项结构体


```c
struct dirent {
    ino_t d_ino;  // 此目录进入点的inode
    ff_t d_off;  // 目录文件开头至此目录进入点的位移
    signed short int d_reclen;  // d_name 的长度，不包含NULL字符
    unsigned char d_type;  // d_name 所指的文件类型
    char d_name[256];  // 文件名
}
```

`d_type`:

    - `DT_BLK`: 块设备
    - `DT-CHR`: 字符设备
    - `DT_DIR`: 目录
    - `DT_LNK`: 软连接
    - `DT_FIFO`: 管道
    - `DT_REG`: 普通文件
    - `DT_SOCK`: 套接字
    - `DT_UNKNOWN`: 未知

- 关闭目录

`int closedir(DIR *dirp);`

-------------------------------------------------------------
1. 复制文件描述符

`int dup(int oldfd);`

    - oldfd: 需要复制的文件描述符
    - 返回值: 新的文件描述符，取最小的且每被占用的文件描述符
    - dup 调用成功: 有两个文件描述符指向同一个文件

`int dup2(int oldfd, int newfd);`

2. 改变已经打开的文件的属性

fcntl，变参函数

复制一个已有的文件描述符，`int ret = fcntl(fd, F_DUPFD);`

获取/设置文件状态标志(open 的flags 参数)

    1. 获取文件状态标识：`int flag = fcntl(fd, F_GETFL);`
    2. 设置文件状态标识: `fcntl(fd, F_SETFL, flag | 其他的标识);`

可以更改的标识: `O_APPEND`, `O_NONBLOCK`














