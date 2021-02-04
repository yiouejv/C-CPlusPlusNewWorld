/*
 *Author: yiouejv
 *Email: yiouejv@126.com
 *Time: 2021-02-03 08:27:56
 *Name: code/lseek.cpp
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
    int fd = open("hello", O_RDWR | O_CREAT, 0777);
    if (fd == -1) {
        perror("open error");
        exit(1);
    }
    lseek(fd, 1000, SEEK_END);
    write(fd, "", SEEK_END);
    close(fd);
    return 0;
}
