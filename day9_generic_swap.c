
/*
자료형이 다른 데이터라도 하나의 함수로 스왑이 기능을 할수있는 예제
*/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>



// generic swap 함수
void generic_swap(void *a, void *b, size_t size)
{
    // void*는 직접 역참조할 수 없음
    // 1바이트 단위로 만들어서 해당 값을 조회하고
    // 입력값으로 size_t로 사이즈가 몇인지 알수있기 떄문에
    // for문으로 1바이트씩 스왑이 가능하다.
    uint8_t *p1 = (uint8_t *)a;
    uint8_t *p2 = (uint8_t *)b;

    // 1바이트씩 교환
    for (size_t i = 0; i < size; i++)
    {
        uint8_t temp = *(p1 + i);

        *(p1 + i) = *(p2 + i);
        *(p2 + i) = temp;
    }
}

// 구조체 정의
typedef struct
{
    char name[10];
    int id;
} Person;



int main(void)
{
    printf("=== Day 9: Generic Swap Implementation ===\n\n");

    // Int

    int a = 10;
    int b = 20;

    printf("[Int] Before: %d, %d\n", a, b);

    generic_swap(&a, &b, sizeof(int));

    printf("[Int] After : %d, %d\n", a, b);

    // Double

    double x = 3.14159;
    double y = 99.99;

    printf("\n[Double] Before: %.5f, %.5f\n", x, y);

    generic_swap(&x, &y, sizeof(double));

    printf("[Double] After : %.5f, %.5f\n", x, y);

    // Struct

    Person p1 = {"Kim", 1};
    Person p2 = {"Lee", 2};

    printf("\n[Struct] Before: %s(%d), %s(%d)\n",
           p1.name, p1.id,
           p2.name, p2.id);

    generic_swap(&p1, &p2, sizeof(Person));

    printf("[Struct] After : %s(%d), %s(%d)\n",
           p1.name, p1.id,
           p2.name, p2.id);

    return 0;
}