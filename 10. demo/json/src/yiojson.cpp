/*
 *Author: yiouejv
 *Email: yiouejv@126.com
 *Time: 2021-02-02 07:08:49
 *Name: yiojson.cpp
*/
#include <cassert>
#include "../include/yiojson.h"

struct yio_context{
    const char* json;
};

static void parse_whitespace(yio_context* c);
static int parse_null(yio_context* c, yio_value* v);
static int parse_true(yio_context* c, yio_value* v);
static int parse_false(yio_context* c, yio_value* v);
static int parse_value(yio_context* c, yio_value* v);

/* 以下实现并没有处理最后的空白字符和PARSE_ROOT_NOT_SINGULAR */
int parse(yio_value* v, const char* json)
{
    yio_context c;
    assert(v != NULL);
    c.json = json;
    v->type = YIO_NULL;
    parse_whitespace(&c);
    return parse_value(&c, v);
}

#define EXPECT(c, ch) do { assert(*c->json == (ch) ); c->json++; } while(0)

static void parse_whitespace(yio_context* c)
{
    const char* p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') ++p;
    c->json = p;
}

static int parse_null(yio_context* c, yio_value* v)
{
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l') {
        return PARSE_INVALID_VALUE;
    }
    c->json += 3;
    v->type = YIO_NULL;
    return PARSE_OK;
}

static int parse_true(yio_context* c, yio_value* v)
{
    EXPECT(c, 't');
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e') {
        return PARSE_INVALID_VALUE;
    }
    c->json += 3;
    v->type = YIO_TRUE;
    return PARSE_OK;
}

static int parse_false(yio_context* c, yio_value* v)
{
    EXPECT(c, 'f');
    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e') {
        return PARSE_INVALID_VALUE;
    }
    c->json += 4;
    v->type = YIO_FALSE;
    return PARSE_OK;
}

static int parse_value(yio_context* c, yio_value* v)
{
    if (*c->json == 'n') return parse_null(c, v);
    else if (*c->json == 't') return parse_true(c, v);
    else if (*c->json == 'f') return parse_false(c, v);
    else if (*c->json == '\0') return PARSE_EXCEPT_VALUE;
    else return PARSE_INVALID_VALUE;
}

