#include <stdio.h>
#include <stdint.h>

// ============================================================
// 1. Naive
// 32개의 비트를 하나씩 확인
// ============================================================
int popcount_naive(uint32_t value)
{
    int count = 0;

    while (value)
    {
        count += value & 1u;
        value >>= 1;
    }

    return count;
}


// ============================================================
// 2. Brian Kernighan
// 가장 오른쪽의 1을 하나씩 제거
//
// value & (value - 1)
// → 가장 오른쪽의 1 하나 제거
// ============================================================
int popcount_kernighan(uint32_t value)
{
    int count = 0;

    while (value)
    {
        value = value & (value - 1);
        count++;
    }

    return count;
}


// ============================================================
// 3. SWAR
// 루프 없이 여러 비트의 개수를 동시에 계산
//
// 2비트 → 4비트 → 8비트 → 16비트 → 32비트
// ============================================================
int popcount_swar(uint32_t value)
{
    // 2비트 그룹별 1의 개수
    value = value - ((value >> 1) & 0x55555555u);

    // 4비트 그룹별 1의 개수
    value = (value & 0x33333333u)
          + ((value >> 2) & 0x33333333u);

    // 8비트 그룹별 1의 개수
    value = (value + (value >> 4))
          & 0x0F0F0F0Fu;

    // 16비트 그룹 합산
    value = value + (value >> 8);

    // 32비트 전체 합산
    value = value + (value >> 16);

    // 결과는 0 ~ 32이므로 하위 6비트만 사용
    return value & 0x3Fu;
}


// ============================================================
// 4. Built-in
// 컴파일러가 제공하는 Population Count 기능
// ============================================================
int popcount_builtin(uint32_t value)
{
#if defined(__GNUC__) || defined(__clang__)

    return __builtin_popcount(value);

#else

    // MSVC 등 built-in을 사용할 수 없는 환경에서는
    // Kernighan 방식으로 대체
    return popcount_kernighan(value);

#endif
}


// ============================================================
// Main
// ============================================================
int main(void)
{
    uint32_t test_cases[] =
    {
        0x00000000u,
        0x00000007u,
        0x12345678u,
        0xFFFFFFFFu
    };

    int count = sizeof(test_cases) / sizeof(test_cases[0]);

    printf("=== Day 5: Population Count (Counting Set Bits) ===\n\n");

    for (int i = 0; i < count; i++)
    {
        uint32_t value = test_cases[i];

        printf("Case %d: Input 0x%08X\n", i + 1, value);

        printf("  [Naive]     : %d\n",
               popcount_naive(value));

        printf("  [Kernighan] : %d (Recommended Logic)\n",
               popcount_kernighan(value));

        printf("  [SWAR]      : %d (Strict Loop-free)\n",
               popcount_swar(value));

        printf("  [Built-in]  : %d\n",
               popcount_builtin(value));

        printf("------------------------------\n");
    }

    return 0;
}