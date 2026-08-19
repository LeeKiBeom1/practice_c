#include <stdio.h>

typedef struct
{
  char a;
  int b;
  double c;
} Sample;
// type이라는 자료형이 들어오면 그걸 0이라는 주소를 사용하는 포인터로 사용하겠다
// 근데 구조체니까 -> 문법이 사용가능해지면서 멤버를 찾아갈 수 있게 되는거고
// 실제 주소값이 필요하니까 &로 또 형변환 해주었고
// 그 주소의 바이트값이 정수형으로 필요해서 (size_t)를 쓰고있는 아주 함축적인 매크로다 
// 이부분 이해하는데 오래걸렸다.
#define my_offsetof(type, member) ((size_t)&(((type *)0)->member))

int main(void)
{
  printf("=== Day 12: offsetof Implementation ===\n\n");
  printf("Struct Size: %zu bytes\n", sizeof(Sample));

  Sample sample;
  // 매크로를 사용하지않고 직접 계산해서 offset을 얻는 방식 
  // a 주소값에서 구조체 주소값을 빼고 size_t로 형변환을 하고있다.
  // (char *)형태로 하는 이유는 char이 1바이트라 1바이트씩 받아서 계산하기 위함이다.
  size_t standard_a = (size_t)((char *)&sample.a - (char *)&sample);

  printf("\n[Standard] Offset of a: %zu\n", standard_a);

  size_t standard_b =
      (size_t)((char *)&sample.b - (char *)&sample);

  printf("[Standard] Offset of b: %zu\n", standard_b);

  size_t standard_c =
      (size_t)((char *)&sample.c - (char *)&sample);

  printf("[Standard] Offset of c: %zu\n", standard_c);
  printf("\n-----------------------------\n\n");

  // 여기서 부터는 위에서 만든 매크로가 실제로 잘 동작하는지 확인하는 코드
  // 매크로의 매개변수에 맞게끔 입력해서 출력결과를 확인하고 직접 계산한 값과 같으면
  // success를 출력한다.
  printf("[My Macro] Offset of a: %zu\n",
         my_offsetof(Sample, a));
  printf("[My Macro] Offset of b: %zu\n",
         my_offsetof(Sample, b));
  printf("[My Macro] Offset of c: %zu\n",
         my_offsetof(Sample, c));
  if (standard_a == my_offsetof(Sample, a) &&
      standard_b == my_offsetof(Sample, b) &&
      standard_c == my_offsetof(Sample, c))
  {
    printf("\n>> Success! Implementation is correct.\n");
  }
  else
  {
    printf("\n>> Failure! Implementation is incorrect.\n");
  }
  return 0;
}