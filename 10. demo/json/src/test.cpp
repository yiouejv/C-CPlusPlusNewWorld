/*
 *Author: yiouejv
 *Email: yiouejv@126.com
 *Time: 2021-02-02 08:50:50
 *Name: src/test.cpp
*/
#include <iostream>
#include "../include/yiojson.h"
using namespace std;

static int test_pass = 0;
static int test_count = 0;

void test_parse_null()
{
    ++test_count;
    yio_value v;
    v.type = YIO_NULL;
    int ret = parse(&v, "null");
    if (ret == PARSE_OK) {
        ++test_pass;
    }else {
        cout << "test_parse_null faild:" << ret << endl;
    }
}

void test_parse_true()
{

}

void test_parse_false()
{

}

void test_invalid_value()
{

}

void test_except_value()
{

}

void test_root_not_singular()
{

}

void test_parse()
{
    test_parse_null();
    test_parse_true();
    test_parse_false();
    test_invalid_value();
    test_except_value();
    test_root_not_singular();
}

int main()
{
    test_parse();
    cout << test_pass << "/" << test_count << " " << test_pass*100.0/test_count << " passed" << endl;
    return 0;
}
