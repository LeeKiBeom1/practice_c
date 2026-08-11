/*
Day 5. 1의 개수 세기 (Population Count)
입력: 32비트 정수
출력: 켜져 있는 비트(1)의 개수
제약조건: 루프(for/while) 없이 비트 연산만으로 구현 (Brian Kernighan 알고리즘 등 활용).
실행결과: 

=== Day 5: Population Count (Counting Set Bits) ===

Case 1: Input 0x00000000
  [Naive]     : 0
  [Kernighan] : 0 (Recommended Logic)
  [SWAR]      : 0 (Strict Loop-free)
  [Built-in]  : 0
------------------------------
Case 2: Input 0x00000007
  [Naive]     : 3
  [Kernighan] : 3 (Recommended Logic)
  [SWAR]      : 3 (Strict Loop-free)
  [Built-in]  : 3
------------------------------
Case 3: Input 0x12345678
  [Naive]     : 13
  [Kernighan] : 13 (Recommended Logic)
  [SWAR]      : 13 (Strict Loop-free)
  [Built-in]  : 13
------------------------------
Case 4: Input 0xFFFFFFFF
  [Naive]     : 32
  [Kernighan] : 32 (Recommended Logic)
  [SWAR]      : 32 (Strict Loop-free)
  [Built-in]  : 32
------------------------------
*/