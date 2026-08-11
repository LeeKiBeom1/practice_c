// #include <stdio.h>

// typedef struct _student
// {
//     char name[10];
//     int num;
//     double grade;
// }student;

// int main(void)
// {
//     student s1;
//     s1.name[0] = 'a';
//     s1.num = 20;
//     s1.grade = 90.5;
// }

// 8바이트 단위로 패딩값을 넣어 용량을 설정한다.
// 구조체 변수의 크기
// 모든 시스템은 데이터를 빠르게 읽고 쓰기 위해 일정한 크기 단위로 메모리에 접근합니다. 
// 컴파일러는 구조체 멤버의 크기가 다를 때 멤버 사이에 패딩 바이트를 넣어 멤버들을 정렬합니다.   
// 이를 바이트 얼라이먼트라고 합니다.  ⇒ 시스템마다 다릅니다. 
// 가장 큰 멤버의 메모리를  할당하는 기준 단위가 됩니다. 
// 구조체는 실행 효율을 위해 패딩 바이트를 넣어 바이트 정렬을 한다.

// 구조체 활용
#include <stdio.h>
#include <stdbool.h>

// 아키텍쳐 부분도 생각하면서 만들어보자

//먼저 구조체의 가장 기본 뼈대만 세우고 이름을 붙여주자
typedef struct
{
    int id;
    float temperature;
    float humidity;
    bool connected;
} SensorData; // 재정의된 자료형의 이름은 대문자로 사용한다.

// 이름만 붙인 구조체에 센서의 정보를 입력하면 넣어주고 출력하는 함수
void print_sensor(const SensorData *sensor) // const를 사용해서 print_sensor함수는 값을 변경시키는 함수가 아니라 읽기만 하는 기능으로 고정시켜 두었다.
                                            // sensor의 주소
{
    printf("센서 번호: %d\n", sensor->id);
    printf("온도: %.1f\n", sensor->temperature);
    printf("습도: %.1f\n", sensor->humidity);
    printf("상태: %s\n",
           sensor->connected ? "연결됨" : "연결 안 됨");
}

void update_sensor(SensorData *sensor,
                   float temperature,
                   float humidity)
{
    sensor->temperature = temperature;
    sensor->humidity = humidity;
    sensor->connected = true;
}

int main(void)
{
    SensorData sensor =
    {
        .id = 1,
        .temperature = 24.5f,
        .humidity = 55.0f,
        .connected = true
    };

    printf("=== 초기 센서 상태 ===\n");
    print_sensor(&sensor); // 매개변수 전달할때 &를 붙이고 안붙이고가 헷갈린다면
                           // 해당 함수의 매개변수 선언부분을 봤을 때 * 가 붙어있다면 &를 붙이고 없다면 안붙인다고 생각하면 쉽다.

    printf("\n=== 센서 값 갱신 ===\n");
    update_sensor(&sensor, 27.3f, 61.2f);
    print_sensor(&sensor);

    return 0;
}