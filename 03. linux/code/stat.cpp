/*
 *Author: yiouejv
 *Email: yiouejv@126.com
 *Time: 2021-02-04 02:14:49
 *Name: code/stat.cpp
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<iostream>
using namespace std;

int main(int argc, const char* argv[])
{
    struct stat buf;
    int r = stat("./copy.cpp", &buf);
    if (r == 0) {
        // 查看文件大小
        cout << buf.st_size << endl;
        // 判断是不是普通文件
        cout << "普通文件: " << ((buf.st_mode & S_IFMT) == S_IFREG) << endl;
        cout << (buf.st_mode & 04) << endl;
    }
    return 0;
}
