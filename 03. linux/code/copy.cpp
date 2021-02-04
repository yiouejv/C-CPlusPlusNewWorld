/*
 *Author: yiouejv
 *Email: yiouejv@126.com
 *Time: 2021-02-03 02:54:13
 *Name: code/copy.cpp
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<iostream>
#include<cstring>
using namespace std;

int main(int argc, const char* argv[])
{
    const char* path = 
 "/share/C-CPlusPlusNewWorld/00. 学习笔记思维导图/operation_system.xmind";
    int fd = open(path, O_RDONLY);
    int tarFd = open("target.xmind", O_WRONLY | O_CREAT, 0777);
    if (fd == -1) {
        cout << path << " 打开失败" << endl;
    }
    if (tarFd == -1) cout << "target.xmind 创建失败" << endl;
    char buf[1024];
    ssize_t len = read(fd, buf, sizeof(buf));
    int i = 0;
    while (len > 0) {
        ++i;
        int ret = write(tarFd, buf, len);
        len = read(fd, buf, sizeof(buf));
        cout << "i: " << i << " ret: "<< ret << endl;
    }
    close(fd);
    close(tarFd);
    return 0;
}
