#include <stdio.h>
#include <stdint.h>

/*
메모리를 복사해서 붙여넣는 과정중 일어날 수 있는
메모리 영역이 오버랩(overlab) 되는 상황을
방지하기 위한 예제
*/


// 어디에 붙여넣을거냐 -> dest / 어디부터 복사할꺼냐 -> src / 복사본의 길이는 뭐냐 -> size
void safe_memmove(uint8_t *dest, uint8_t *src, int size)
{
    // 목적지가 원본보다 뒤에 있으면
    // 원본 데이터가 덮어써지는 것을 막기 위해 뒤에서부터 복사
    if (dest > src)
    {
        for (int i = size - 1; i >= 0; i--)
        {
            *(dest + i) = *(src + i);
        }
    }
    // 목적지가 원본보다 앞에 있으면
    // 앞에서부터 복사
    else
    {
        for (int i = 0; i < size; i++)
        {
            *(dest + i) = *(src + i);
        }
    }
}


// 배열 출력
void print_data(uint8_t *data, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%02X ", *(data + i));
    }

    printf("\n");
}


// 두 배열 비교
int compare_data(uint8_t *data1, uint8_t *data2, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (*(data1 + i) != *(data2 + i))
        {
            return 0;
        }
    }

    return 1;
}


int main(void)
{
    printf("=== Day 8: Safe Memcpy (memmove) Implementation ===\n\n");


    // Test 1 : 오른쪽으로 2바이트 이동

    uint8_t data1[10] = {
        0x01, 0x02, 0x03, 0x04, 0x05,
        0x06, 0x07, 0x08, 0x09, 0x0A
    };

    uint8_t expected1[10] = {
        0x01, 0x02, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x08, 0x09, 0x0A
    };


    printf("[Initial] ");
    print_data(data1, 10);

    printf("\nTest 1: Overlap (Dest > Src) -> Shift Right 2 bytes\n");

    // 0~4번의 5바이트를 2~6번으로 복사
    safe_memmove(
        &data1[2],
        &data1[0],
        5
    );

    printf("[Result ] ");
    print_data(data1, 10);

    if (compare_data(data1, expected1, 10))
    {
        printf(">> Success!\n");
    }
    else
    {
        printf(">> Fail!\n");
    }

    // Test 2 : 왼쪽으로 2바이트 이동

    uint8_t data2[10] = {
        0x01, 0x02, 0x03, 0x04, 0x05,
        0x06, 0x07, 0x08, 0x09, 0x0A
    };

    uint8_t expected2[10] = {
        0x03, 0x04, 0x05, 0x06, 0x07,
        0x06, 0x07, 0x08, 0x09, 0x0A
    };


    printf("\n[Initial] ");
    print_data(data2, 10);

    printf("\nTest 2: Overlap (Dest < Src) -> Shift Left 2 bytes\n");

    // 2~6번의 5바이트를 0~4번으로 복사
    safe_memmove(
        &data2[0],
        &data2[2],
        5
    );

    printf("[Result ] ");
    print_data(data2, 10);

    if (compare_data(data2, expected2, 10))
    {
        printf(">> Success!\n");
    }
    else
    {
        printf(">> Fail!\n");
    }


    return 0;
}
