#ifndef __YIOJSON__
#define __YIOJSON__

typedef enum {
    YIO_NULL,
    YIO_FALSE,
    YIO_TRUE,
    YIO_NUMBER,
    YIO_STRING,
    YIO_ARRAY,
    YIO_OBJECT,
} yio_type;

typedef struct {
    yio_type type;
} yio_value;

enum {
    PARSE_OK = 0,
    PARSE_EXCEPT_VALUE,
    PARSE_INVALID_VALUE,
    PARSE_ROOT_NOT_SINGULAR,
};

int parse(yio_value* v, const char* json);
yio_type get_yio_type(const yio_value* v);


#endif  // __YIOJSON__
