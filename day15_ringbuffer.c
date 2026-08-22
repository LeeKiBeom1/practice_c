#include <stdbool.h>  // bool, true, false
#include <stdint.h>   // uint8_t
#include <stdio.h>    // printf

#define BUFFER_SIZE 8

// 원형버퍼
// 고정 크기 배열의 끝과 시작을 연결해서 둥근 원처럼 반복해서 사용하는 버퍼

typedef struct {
    uint8_t data[BUFFER_SIZE];
    // 중요! 마지막으로 넣은 위치가아닌 다음에 넣을 위치와 꺼낼 위치다 저번에 했던 다음 블록을 가리키는 next와 비슷한 구조다
    // next는 주소값이였지만 여기서는 배열의 값이다.
    int head;  // 다음 데이터를 저장할 위치
    int tail;  // 다음 데이터를 꺼낼 위치
} RingBuffer;

// 빈 원형 버퍼로 초기화한다.
void rb_init(RingBuffer *rb) {
    rb->head = 0;
    rb->tail = 0;
}

// head와 tail이 같으면 저장된 데이터가 없다.
bool rb_is_empty(const RingBuffer *rb) {
    return rb->head == rb->tail;
}

// head의 다음 위치가 tail이면 더 저장할 공간이 없다.
// Full과 Empty를 구분하기 위해 배열의 한 칸은 항상 비워 둔다.
bool rb_is_full(const RingBuffer *rb) {
    // % BUFFER_SIZE 이 로직이 핵심인데 
    // 8로 나누고 나머지를 찾으면 8미만인 값에선 계속 0 -> 1 -> 2 -> 3 ... 올라가다가 8을 만나면 나머지가 0이되면서 다시 0 -> 1 -> 2 ...
    // 이 로직은 다른 함수에서도 반복 등장한다.
    int next_head = (rb->head + 1) % BUFFER_SIZE;
    return next_head == rb->tail;
}

// 성공하면 데이터를 저장하고 true, 버퍼가 가득 찼으면 false를 반환한다.
bool rb_put(RingBuffer *rb, uint8_t value) {
    if (rb_is_full(rb)) {
        return false;
    }

    rb->data[rb->head] = value;
    rb->head = (rb->head + 1) % BUFFER_SIZE;
    return true;
}

// 성공하면 꺼낸 데이터를 output에 저장하고 true를 반환한다.
// 버퍼가 비어 있으면 false를 반환한다.
bool rb_get(RingBuffer *rb, uint8_t *output) {
    if (rb_is_empty(rb) || output == NULL) {
        return false;
    }

    *output = rb->data[rb->tail];
    rb->tail = (rb->tail + 1) % BUFFER_SIZE;
    return true;
}

// ---- 테스트 코드 ----
int main(void) {
    RingBuffer uart_rx_buf;
    uint8_t temp;
      
    rb_init(&uart_rx_buf);
      
    printf("--- Phase 1: Filling Buffer ---\n");
    // 버퍼 사이즈가 8이므로, 한 칸 비우면 최대 7개 저장 가능
    for (int i = 1; i <= 8; i++) {
        if (rb_put(&uart_rx_buf, i)) {
            printf("Put: %d (Head: %d, Tail: %d)\n", i, uart_rx_buf.head, uart_rx_buf.tail);
        } else {
            printf("Fail to Put: %d (Buffer Full!)\n", i);
        }
    }
      
    printf("\n--- Phase 2: Reading Buffer ---\n");
    // 3개만 읽어봄
    for (int i = 0; i < 3; i++) {
        if (rb_get(&uart_rx_buf, &temp)) {
            printf("Get: %d (Head: %d, Tail: %d)\n", temp, uart_rx_buf.head, uart_rx_buf.tail);
        }
    }
      
    printf("\n--- Phase 3: Writing again (Wrap around) ---\n");
    // 읽어서 공간이 생겼으므로 다시 쓰기 가능 (인덱스가 0으로 돌아가는지 확인)
    if (rb_put(&uart_rx_buf, 99)) {
         printf("Put: 99 (Head: %d, Tail: %d)\n", uart_rx_buf.head, uart_rx_buf.tail);
    }
      
    return 0;
}
