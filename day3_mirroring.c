
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

uint8_t reverse_bits8(uint8_t value)
{
    // 1단계: 상위 4비트와 하위 4비트 교환
    value = (uint8_t)(((value & 0xF0u) >> 4) |
                      ((value & 0x0Fu) << 4));

    // 2단계: 2비트 단위로 교환
    value = (uint8_t)(((value & 0xCCu) >> 2) |
                      ((value & 0x33u) << 2));

    // 3단계: 1비트 단위로 교환
    value = (uint8_t)(((value & 0xAAu) >> 1) |
                      ((value & 0x55u) << 1));

    return value;
}

void print_binary8(uint8_t value)
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (value >> i) & 1u);

        if (i == 4)
        {
            printf(" ");
        }
    }
}

void test_reverse(uint8_t input)
{
    uint8_t output = reverse_bits8(input);
    uint8_t verify = reverse_bits8(output);

    printf("Input : 0x%02X (", input);
    print_binary8(input);
    printf(")\n");

    printf("Output: 0x%02X (", output);
    print_binary8(output);
    printf(")\n");

    printf("Verify: %s\n", verify == input ? "OK" : "FAIL");
    printf("------------------------\n");
}

int main(void)
{
    printf("=== Day 4: Bitwise Reverse (Mirroring) ===\n\n");

    test_reverse(0xD2);
    test_reverse(0x0F);
    test_reverse(0xAA);
    test_reverse(0x12);

    return 0;
}