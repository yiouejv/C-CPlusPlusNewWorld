/*
 *Author: yiouejv
 *Email: yiouejv@126.com
 *Time: 2021-02-04 08:54:13
 *Name: code/iterdir.cpp
*/

#include<iostream>
#include<sys/types.h>
#include<dirent.h>
#include<cstring>
using namespace std;


void iterDir(const char* dirname) {
    DIR* dir = opendir(dirname);
    dirent* de = NULL;
    while ((de = readdir(dir)) != NULL){
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0 || strcmp(".git", de->d_name) == 0) continue;
        if (de->d_type == DT_REG) {
            char filename[1024] = {0};
            strcat(filename, dirname);
            strcat(filename, "/");
            strcat(filename, de->d_name);
            cout << "普通文件: " << filename << endl;
        } else if (de->d_type == DT_DIR) {
            char path[1024] = {0};
            sprintf(path, "%s/%s", dirname, de->d_name);
            iterDir(path);
        } else {
            cout << "非普通文件: " << de->d_name << endl;
        }
    }
    closedir(dir);
}



int main(int argc, const char* argv[])
{
    iterDir(argv[1]);
    return 0;
}
