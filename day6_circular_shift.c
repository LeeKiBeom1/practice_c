#include <stdio.h>
#include <stdint.h>

// 왼쪽 원형 회전
uint32_t rotate_left(uint32_t value, unsigned int n)
{
    n %= 32; // 어떤 숫자가 들어와도 0 ~ 31안의 범위에서 돌게끔 하기위함

    if (n == 0)
        return value;

    return (value << n) | (value >> (32 - n));
    /*
    원리는 왼쪽으로 n칸 밀어낸 값과  총비트 - n 만큼 오른쪽으로 민값을 | 오아연산하면 결과적으로 왼쪽으로 로테이션되는 비트값이 나온다.
    ex) 1001
    왼쪽으로 1칸 밀음 << 1
    0010
    전체비트-밀어버린칸(1)만큼 반대로 밈 >> (4 - 1)
    0001
    오아연산 -> |
    0011
    결과물 왼쪽으로 한칸 데이터를 밀되 다시 처음으로 돌아오는 형태가 완성
    
    */
}

// 오른쪽 원형 회전
uint32_t rotate_right(uint32_t value, unsigned int n)
{
    n %= 32;

    if (n == 0)
        return value;

    return (value >> n) | (value << (32 - n));
}

// 32비트 이진수 출력
void print_binary32(uint32_t value)
{
    for (int i = 31; i >= 0; i--)
    {
        printf("%u", (value >> i) & 1u); // 출력은 가장 왼쪽의 비트부터 출력해야하니까 31만큼 왼쪽으로 밀고 1과 앤드연산해서 출력하고 30만큼밀고 ... 반복하면 원하는 결과물을 만들 수 있다.

        if (i % 4 == 0)
            printf(" ");
    }

    printf("\n");
}

int main(void)
{
    uint32_t data = 0xF0000000;

    printf("=== Day 6: Circular Shift (Rotate) ===\n\n");

    printf("[Init]   Hex: 0x%08X\n", (unsigned int)data);
    printf("         Bin: ");
    print_binary32(data);

    // ROL 4
    data = rotate_left(data, 4);

    printf("\n[ROL 4]  Hex: 0x%08X\n", (unsigned int)data);
    printf("         Bin: ");
    print_binary32(data);
    printf("         (MSB bits moved to LSB)\n");

    // ROR 4
    data = rotate_right(data, 4);

    printf("\n[ROR 4]  Hex: 0x%08X\n", (unsigned int)data);
    printf("         Bin: ");
    print_binary32(data);
    printf("         (Restored to original)\n");

    // Test 2
    uint32_t test = 0x12345678;
    uint32_t result = rotate_right(test, 8);

    printf("\n[Test 2] Data: 0x%08X -> ROR 8 -> 0x%08X\n",
           (unsigned int)test,
           (unsigned int)result);

    return 0;
}