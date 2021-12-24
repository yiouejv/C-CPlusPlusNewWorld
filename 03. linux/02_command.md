

### tree

- tree: 查看当前目录
- tree dir: 查看指定目录
- tree -a: 查看所有文件
- tree -d: 仅显示目录
- tree -L: level, 显示目录的层级
- tree -f: 显示全路径


### ls

查看文件或目录

- ls -a: 所有的文件
- ls -l: 显示详细信息
- ls -h: 以人类能看懂的方式显示, -human
- ls -F: 如果是目录，后面加个/



### pwd

print work directory


### mkdir

- mkdir -p: 创建多级目录

    mkdir -p aa/bb/cc

- mkdir -v: 打印执行结果


### rm

- rm -i: 二次确认
- rm -r: 递归
- rm -f: 强制

### cp

cp file1 file2,  file2 不存在则创建，存在则覆盖   
cp file1 dir1, 拷贝到目录里    
cp dir1 dir2 -r, 拷贝dir1到dir2   


### ln

创建软链接

ln -s 文件名  快捷方式名

文件名需要使用绝对路径


创建硬链接

ln 文件名 文件名

<img src="./images/file_link.png">


硬链接的使用场景:

磁盘上由一个文件，/home/xxx/hello

在其他多个目录中管理hello，并能实际同步。

### chmod

修改权限

chmod who[+-=] mode 文件名

who:
```
    - u: user 文件所有者
    - g: group 文件所属组
    - o: other 其他人
    - a: all 所有人
```
+-=:  增加，减去，覆盖权限   
mode: rwx, 读写执行


方式二：

chmod [+-=] mode 文件名

r: 4, w: 2, x: 1, -: 0

文件所有者和所属者减去r:  chmod -440 filename

**目录没有执行权限，用户是进不去的**

### chown

修改文件所有者和所属组

chown 新的所有者 文件名   
chown 新的所有者:新的组 文件名


### find

- 根据文件名查找: find 查找目录 -name "文件名"
- 根据文件类型查找: find 查找目录 -type 文件类型

    普通文件原本用`-`表示， find 这里用f

- 根据文件大小查找: find 查找目录 -size +10k
    
    +: 大于，- 小于，=就不写

    单位: k, M 注意大小写

    查找当前目录大于10k，小于100k: find . -size +10k -size -100k

- 根据日期查找: 

    - 创建日期: -ctime, 修改日期: -mtime, 访问日期: -atime
    - -n/+n:  -n 代表n天以内, +n n天以前

    例: `find . -ctime -1`

- 根据深度做搜索:

    `-maxdepth n` 指定一个最深的层数   
    `-mindepth n` 搜索n层以上的目录


总结： find 搜索的路径 参数 搜索的内容


高级查找: 查找指定目录，并列出该目录中文件的详细信息

    - 效率低: 

        `find . -type d -exec shell命令 {} \;`

        `find . -type d -ok shell命令 {} \;`

    - 效率高

        `find . -type d | xargs shell命令`
    


### grep

根据文件内容查找

grep -r(有子目录) "查找的内容" 搜索的路径

-n: 显示查出结果在文件第几行



### 压缩包管理

.gz      --gzip   
.bz2     --bzip2

tar: 打包

- c: 创建压缩文件
- x: 释放压缩文件
- v: 打印提示信息
- f: 指定压缩包的名字
- z: 使用gzip 压缩文件   -- xxx.tar.gz
- j: 使用bzip2 的方式压缩文件  -- xxx.tar.bz2

`tar -czvf blog.tar.gz blog`   
`tar -xzvf blog.tar.gz -C 指定目录`

rar: 需要安装

压缩: rar a -r 压缩包名(不需要指定后缀) 压缩的内容   
解压: rar x 压缩包名 解压路径  

zip:

压缩: zip a -r 压缩包名(不需要指定后缀) 压缩的内容   
解压: unzip 压缩包的名字 -d 解压目录   


### apt

ubuntu apt-get

1. 在线安装

    - 安装： sudo apt-get install 安装包的名字
    - 卸载: sudo apt-get remove 软件的名字
    - 软件列表的更新: sudo apt-get update
    - 清空缓存: sudo apt-get clean
        
        var/cache/apt/archives

2. 软件包安装 (ubuntu 下 .deb格式)

    - 安装: sudo dpkg -i 包名
    - 卸载: sudo dpkg -r 软件的名字




    






