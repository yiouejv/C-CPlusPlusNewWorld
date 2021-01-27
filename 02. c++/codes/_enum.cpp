#include<iostream>
using namespace std;

enum openModes {
    open, close, read=5, write
};

int main(int argc, char const *argv[])
{
    openModes a = open;
    cout << a << endl;

    openModes b = close;
    cout << b << endl;

    openModes c = write;
    cout << c << endl;
    return 0;
}