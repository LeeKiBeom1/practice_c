#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint32_t value = 31;

    int count = 0;

    while(value != 0) // while(value)도 가능한데 while자체가 bool로 판단하기 때문에 value가 0이 되는 순간 while문을 탈출한다.
    {
        printf("%u\n", value);
        value = value & (value - 1); // value &= value - 1; 도 가능하다.
        count++;
        printf("%u\n", value);
    }

    printf("%d\n", count);
    return 0;
}