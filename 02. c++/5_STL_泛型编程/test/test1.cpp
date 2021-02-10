/*
 *Author: yiouejv
 *Email: yiouejv@126.com
 *Time: 2021-02-10 06:10:57
 *Name: test/test1.cpp
*/

#include<iostream>
#include<vector>
using namespace std;

int main(int argc, const char* argv[])
{
    vector<int> v{1,2,3,4,5,6};
    for (auto i: v) {
        cout << i << " ";
    }
    cout << endl;

    for (int& i: v){
        i *= i;
    }
    for (auto i: v) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
