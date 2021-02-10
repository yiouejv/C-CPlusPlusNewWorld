### 自定义 startup code

```cpp
// entrypoint.c
include<stdio.h>
#include<stdlib.h>

int blabla() 
{
    printf("blabla");
    exit(0);
}


int main() {
    printf("main");
    
}
```

`gcc entrypoint.c -e blabla`

`./a.out`

输出: blabla



