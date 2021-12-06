#include<stdio.h>

extern int x,y;

// extern int foo(int a, int b);
extern int foo;
int main()
{
    // printf("%d + %d = %d\n", x, y, foo(x,y) );
    printf("%x\n", foo );
    foo = 1;
}