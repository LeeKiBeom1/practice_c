// 이진수로 표현한 값의 1이 총 몇개냐를 구하는 문제

#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint32_t value = 7;

    printf("%u\n", value & 1u);

    return 0;
}