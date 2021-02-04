/*
 *Author: yiouejv
 *Email: yiouejv@126.com
 *Time: 2021-02-03 02:13:07
 *Name: code/open.cpp
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<iostream>
using namespace std;

int main(int argc, const char* argv[])
{
    // 打开一个文件，hello
    int fd = open("./hello", O_RDWR | O_CREAT, 0777);
    if (fd == -1) {
        cout << "文件打开失败！" << endl;
    }
    close(fd);
    return 0;
}
