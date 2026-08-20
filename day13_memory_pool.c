#include <stdint.h> // uint8_t를 사용하기 위한 헤더
#include <stdio.h>  // printf를 사용하기 위한 헤더

// 설정: 블록 크기와 개수
#define BLOCK_SIZE  32
#define POOL_SIZE   10

// 메모리 블록 구조체 (Free List 관리를 위한 연결 리스트 노드)
// 할당되지 않았을 때는 다음 빈 블록을 가리키는 포인터로 사용됨
typedef struct Block {
    struct Block* next;
} Block;

// 메모리 풀 컨텍스트
typedef struct {
    // 실제 메모리 공간 (바이트 배열)
    // 320바이트의 메모리 공간이 생겼다.
    uint8_t memory_area[POOL_SIZE * BLOCK_SIZE];

    // 현재 사용 가능한 첫 번째 블록을 가리키는 포인터
    Block* free_list;

    // 디버깅용: 현재 사용 중인 블록 수
    int used_count;
} MemoryPool;

// 프로그램이 실제로 사용할 메모리 풀
MemoryPool my_pool;

// 1. 초기화: 모든 메모리를 쪼개서 연결 -> 리스트로 연결
void pool_init(MemoryPool* pool) {
    // 아직 사용 중인 블록은 하나도 없다.
    pool->used_count = 0;

    // memory_area를 BLOCK_SIZE(32바이트) 간격으로 나누어 연결한다.
    for (int i = 0; i < POOL_SIZE; i++) {
        // i번째 블록의 시작 주소를 구한다.
        Block *current = (Block *)(pool->memory_area + i * BLOCK_SIZE);

        if (i == POOL_SIZE - 1) {
            // 마지막 블록 뒤에는 더 이상 빈 블록이 없다.
            current->next = NULL;
        } else {
            // 현재 블록이 다음 빈 블록을 가리키게 한다.
            current->next = (Block *)(pool->memory_area
                                      + (i + 1) * BLOCK_SIZE);
        }
    }

    // Free List의 시작점은 0번째 블록이다.
    pool->free_list = (Block *)pool->memory_area;

    printf("[Init] Memory Pool Initialized (%d blocks of %d bytes)\n",
           POOL_SIZE, BLOCK_SIZE);
}

// 2. 할당: Free List의 헤드(Head)를 떼어줌 (Pop)
void* pool_alloc(MemoryPool* pool) {
    // 빈 블록이 하나도 남지 않았다면 할당에 실패한다.
    if (pool->free_list == NULL) {
        return NULL;
    }

    // Free List의 첫 번째 블록을 꺼낼 대상으로 기억한다.
    Block *allocated = pool->free_list;

    // Free List의 시작점을 그다음 빈 블록으로 옮긴다.
    pool->free_list = allocated->next;

    // 사용 중인 블록 수를 1 증가시킨다.
    pool->used_count++;

    // 꺼낸 블록의 시작 주소를 사용자에게 반환한다.
    return allocated;
}

// 3. 해제: 반환된 블록을 Free List의 헤드에 다시 붙임 (Push)
void pool_free(MemoryPool* pool, void* ptr) {
    // NULL은 반환할 메모리가 없다는 뜻이므로 아무것도 하지 않는다.
    if (ptr == NULL) {
        return;
    }

    // 반환받은 주소를 다시 Block 포인터로 사용한다.
    Block *returned = (Block *)ptr;

    // 반환된 블록 뒤에 기존 Free List를 연결한다.
    returned->next = pool->free_list;

    // 반환된 블록을 Free List의 새로운 첫 번째 블록으로 만든다.
    pool->free_list = returned;

    // 사용 중인 블록 수를 1 감소시킨다.
    pool->used_count--;
}

// 테스트 코드
int main(void) {
    pool_init(&my_pool);

    // 3개 할당
    void* p1 = pool_alloc(&my_pool);
    void* p2 = pool_alloc(&my_pool);
    void* p3 = pool_alloc(&my_pool);

    printf("Allocated: %p, %p, %p\n", p1, p2, p3);
    printf("Used Blocks: %d\n", my_pool.used_count);

    // 1개 해제 (p2)
    printf("Freeing %p...\n", p2);
    pool_free(&my_pool, p2); // 이제 p2가 free_list의 head가 됨

    // 다시 1개 할당 (p2와 같은 주소가 나와야 함 - LIFO 특성)
    void* p4 = pool_alloc(&my_pool);
    printf("Re-allocated: %p (Should be same as old p2)\n", p4);

    return 0;
}
// 와 이거 굉장히 머리를 많이 써야하네
// 이해하는데 너무 힘들었다.
