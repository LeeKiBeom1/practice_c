#include <stddef.h>  // size_t
#include <stdint.h>  // uint8_t, uint32_t
#include <stdio.h>   // printf, putchar

#define BYTES_PER_LINE 16

typedef struct {
    uint32_t id;
    char name[12];
    float value;
} SensorData;

// 메모리를 1바이트씩 읽어 16진수와 ASCII로 함께 출력한다.
// adress에는 문자열, 구조체, 정수 여러가지 자료형의 주소가 들어올 수 있으므로
// void *address 해주었다.
void hexdump(const char *title, const void *address, size_t length) {
    // adress가 const void형태로 들어왔기 때문에 1byte씩 읽기위해서
    // uint8로 형변환해주었다.
    const uint8_t *bytes = (const uint8_t *)address;

    printf("%s:\n", title);

    // 메모리를 한줄에 16바이트씩 출력하는 코드
    for (size_t offset = 0; offset < length; offset += BYTES_PER_LINE) { // 한번 돌때마다 16씩 증가중
        printf("  %04zx  ", offset);

        // 현재 줄의 16바이트 씩 출력
        // offset은 줄 i는 바이트 순서라고 생각하면된다.
        for (size_t i = 0; i < BYTES_PER_LINE; ++i) {
            if (offset + i < length) {
                // 16진수 출력
                printf("%02x ", (unsigned int)bytes[offset + i]);
            } else {
                printf("   ");
            }
        }

        putchar(' ');

        // ASCII 영역: 출력 가능한 문자는 그대로, 나머지는 '.'으로 표시한다.
        for (size_t i = 0;
             i < BYTES_PER_LINE && offset + i < length;
             ++i) {
            uint8_t byte = bytes[offset + i];
            // 아스키 출력 아스키 코드값 범위에 있다면 그대로 출력 아닐경우 . 출력
            putchar(byte >= 0x20 && byte <= 0x7e ? (char)byte : '.');
        }

        putchar('\n');
    }

    putchar('\n');
}

int main(void) {
    // 테스트 1: 단순 문자열 (마지막 널 문자까지 출력)
    char my_text[] = "Hello Embedded World! This is Hexdump.";
    hexdump("String Dump", my_text, sizeof(my_text));

    // 테스트 2: 구조체의 정수 엔디안과 float 메모리 표현 확인
    SensorData sensor = {0x12345678, "Sensor A", 3.14f};
    hexdump("Struct Dump", &sensor, sizeof(sensor));
    // 16진수 값, float값은 문자로 출력이 안된다. 근데 이상한 문자열이 나온건 그냥 1바이트씩 읽었는데 우연히 아스키코드값과 겹쳐서 저렇게 출력됬다.

    return 0;
}
