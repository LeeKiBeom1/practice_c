#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int rows = 3;
    int cols = 4;

    // 이중 포인터 - 포인터를 담는 포인터
    int **matrix;

    // 1. 각 행의 시작 주소를 저장할 포인터 배열 할당
    // malloc(필요한바이트수);
    // 행의 바이트수는 rows * sizof(int)이지만
    // 실제 행에는 인트값이 아닌 인트 주소값이 들어가므로
    // (int *)가 들어간다.
    // **matrix 에는 int 값이 들어가는것이 아닌 int * 값이 들어오는 것이다.
    // int 자체는 4byte고 int *는 64bit환경에선 보통8byte값이 들어간다.
    matrix = malloc(rows * sizeof(int *));

    // 2. 실제 데이터를 저장할 연속된 메모리 공간 할당
    // 모든 데이터의 실제값이 들어가므로 sizeof(int)를 사용한다.
    int *data = malloc(rows * cols * sizeof(int));

    // 3. 각 행 포인터를 실제 데이터 영역의 시작 위치와 연결
    for (int i = 0; i < rows; i++)
    {
        // 1행 1열 index[0] 데이터의 주소값을 저장
        // 2행 1열 index[1*4] 데이터의 주소값을 저장 ...
        // 주소값을 저장했으므로 주소값을 참조하여 해당 값에 접근이 가능해진다.
        matrix[i] = data + (i * cols);
    }

    // 4. 예시의 1 ~ 12 값 저장
    int value = 1;

    // 2중 for문 행 -> 열 순서로 사용
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = value;
            value++;
        }
    }

    // 5. 출력
    printf("=== Day 10: Dynamic 2D Array Allocation ===\n\n");

    printf("Generated Matrix (%dx%d):\n", rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%2d ", matrix[i][j]);
        }

        printf("\n");
    }

    // 6. 동적 메모리 해제
    free(data);
    free(matrix);

    printf("\n>> Memory successfully freed.\n");

    return 0;
}