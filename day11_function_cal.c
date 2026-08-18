#include <stdio.h>

// enum -> 숫자에 이름을 붙이는 문법
// 자동으로 0부터1씩 증가하면서 숫자를 부여한다
// enum 열거형의이름 {사용할 값들의 목록} 이런식으로 사용
enum Operation
{
    ADD, // 0
    SUB, // 1 ...
    MUL,
    DIV,
    EXIT
};

int add(int a, int b)
{
    return a + b;
}
int sub(int a, int b)
{
    return a - b;
}
int mul(int a, int b)
{
    return a * b;
}
int divide(int a, int b)
{
    return a / b;
}
// enum Operaion을 반환하는 함수 struct Person과 비슷한 개념
enum Operation select_operation(void)
{
    int input;

    printf("Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): ");
    scanf("%d", &input);

    // 설정 범위 밖 숫자를 입력할 때의 예외 처리
    while (input < ADD || input > EXIT)
    {
        printf("잘못된 범위 입니다. 0 ~ 4 값을 입력해 주세요.\n");
        printf("Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): ");
        scanf("%d", &input);
    }

    return input;
}

int main(void)
{
    printf("=== Day 11: Function Pointer Array Calculator ===\n\n");
    // operation은 포인터 + [4]칸 배열이고 int두개를 받는 함수이며 int를 반환한다 라는 뜻!
    int (*operations[4])(int, int) =
        {
            add, sub, mul, divide};

    enum Operation selected;

    selected = select_operation();

    int a;
    int b;
    int result;
    while (selected != EXIT)
    {
        printf("Input two integers: ");
        scanf("%d %d", &a, &b);
        // 맥에서는 동작은 하는데 c에선 원래 0으로 나누면 에러나서 해주는 예외처리
        while (selected == DIV && b == 0)
        {
            printf("두 번째 숫자는 0이 될 수 없습니다. 다시 입력하세요: ");
            scanf("%d %d", &a, &b);
        }

        result = operations[selected](a, b);

        printf(">> Result: %d\n\n", result);

        selected = select_operation();
    }

    return 0;
}
