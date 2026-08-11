// 포인터 함수를 공부해보자

#include <stdio.h>

void hello(void)
{
    printf("hello world\n");
}

int main(void)
{
    void (*function_porinter)(void);

    function_porinter = hello;

    function_porinter();
    
    return 0;
}