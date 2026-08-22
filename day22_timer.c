#include <stdbool.h>  // bool
#include <stdint.h>   // uint32_t
#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, free

typedef void (*TimerCallback)(int timer_id);

typedef struct TimerNode {
    int id;
    uint32_t delta_time;       // 앞 타이머 만료 후 추가로 기다릴 시간
    TimerCallback callback;
    struct TimerNode *next;
} TimerNode;

static TimerNode *timer_head = NULL;

// 타이머가 만료되었을 때 실행되는 콜백 함수
void on_timer_expired(int timer_id) {
    printf(">> [Event] Timer %d expired! Action executed.\n", timer_id);
}

// 리스트에 저장된 상대 시간과 실제 총 남은 시간을 함께 출력한다.
void print_timer_list(void) {
    // head로 설정한 타이머부터 순서대로 출력
    // 순서는 current->next로 알수있다.
    const TimerNode *current = timer_head;
    uint32_t total_time = 0;

    printf("[Timer List] ");

    while (current != NULL) {
        total_time += current->delta_time;
        printf("(ID:%d, dt:%u, total:%u) -> ",
               current->id,
               (unsigned int)current->delta_time,
               (unsigned int)total_time);
        current = current->next;
    }

    printf("NULL\n");
}

// 새 타이머를 만료 시간 순서에 맞게 Delta List에 삽입한다.
// bool 인 이유?
// 타이머 노드는 malloc으로 만드는데
// 메모리 할당에 성공하면 true 실패하면 false를 반환하기 때문이다.
// set_timer에 역할이 아주많은데
// 여러개의 타이머가 들어오기 때문에 
// 각 타이머의 
bool set_timer(int id, uint32_t milliseconds) {
    // 먼저 malloc로 타이머를 담을 공간을 설정
    TimerNode *new_timer = malloc(sizeof(*new_timer));

    if (new_timer == NULL) {
        return false;
    }
    // 구조체 각 멤버에 값 설정
    new_timer->id = id;
    new_timer->delta_time = milliseconds;
    new_timer->callback = on_timer_expired;
    new_timer->next = NULL;

    TimerNode *previous = NULL;
    TimerNode *current = timer_head;

    // 앞 노드들의 상대 시간을 빼며 삽입할 위치를 찾는다.
    // 새 타이머의 시간이 현재 노드의 시간보다 크거나 같으면
    // 현재 노드를 지나가고, 더작으면 현재 노드 앞에서 멈춘다.
    // 예시를 들면
    /* 
    기존: 5 → 10 → 15
    새 값: 7

    7 >= 5  → 5를 지나감
    7 >= 10 → 거짓, 10 앞에서 멈춤

    5 → 7 → 10 → 15
    */
    while (current != NULL && new_timer->delta_time >= current->delta_time) {
        // 현재 노드의 시간을 뺌
        new_timer->delta_time -= current->delta_time;
        // 옮길 공간 만들고
        previous = current;
        // current는 다음 노드로 변경후 저장
        current = current->next;
    }

    new_timer->next = current;

    // 새 노드가 중간에 들어가면 뒤 노드의 상대 시간을 줄인다.
    // previous -> 새 타이머 바로 앞의 노드
    // current -> 새 타이머 바로 뒤의 노드
    // 새 타이머 뒤에 기존타이머가 있다면
    if (current != NULL) {
         // 기존 타이머가 10ms 남았는데 새타이머가 5ms들어왔다면
         // 10 - 5 해서 새 타이머가 끝난뒤 5ms만 더기다리면 끝나게끔 하기위함
        current->delta_time -= new_timer->delta_time;
    }

    // 새 타이머가 맨앞에 들어간다면
    if (previous == NULL) {
        // 새 타이머가 리스트의 첫번째 노드가 되고 헤드로 인서트 됬다 출력
        timer_head = new_timer;
        printf("Timer %d set (%u ms) [Inserted at HEAD]\n",
               id, (unsigned int)milliseconds);
    } else {
        // 헤드가 아니면 list로 인서트 되었다 출력
        previous->next = new_timer;
        printf("Timer %d set (%u ms) [Inserted in List]\n",
               id, (unsigned int)milliseconds);
    }

    print_timer_list();
    return true;
}

// 1ms가 지났다고 가정하고 맨 앞 노드의 시간만 감소시킨다.
void tick(void) {
    if (timer_head == NULL) {
        printf("All timers cleared.\n");
        return;
    }

    if (timer_head->delta_time > 0) {
        timer_head->delta_time--;
    }

    // 같은 시점에 만료되는 타이머들은 delta_time이 연속으로 0이 된다.
    while (timer_head != NULL && timer_head->delta_time == 0) {
        TimerNode *expired = timer_head;
        timer_head = timer_head->next;

        expired->callback(expired->id);
        free(expired);
    }

    if (timer_head != NULL) {
        printf("Rem Head dt: %u\n", (unsigned int)timer_head->delta_time);
    } else {
        printf("All timers cleared.\n");
    }
}

// 프로그램 종료 전에 남아 있는 타이머 메모리를 모두 해제한다.
void clear_timers(void) {
    while (timer_head != NULL) {
        TimerNode *next = timer_head->next;
        free(timer_head);
        timer_head = next;
    }
}

int main(void) {
    printf("=== Day 22: Software Timer (Delta List) ===\n\n");

    // 1번 타이머 10ms후 만료 2번 타이머 5ms 후 만료 3번 타이머 15ms 후 만료
    // 가드문을 못타면 fail뜨고 클리어 타이머 해버림
    // set_timer가 bool 반환하기 때문에 !붙여서 set타이머가 성공하면? if문 탈출 실패하면? if문 실행
    if (!set_timer(1, 10) || !set_timer(2, 5) || !set_timer(3, 15)) {
        printf("Failed to allocate timer memory.\n");
        clear_timers();
        return 1;
    }

    printf("\n>> Start Ticking...\n");

    for (int tick_count = 1; tick_count <= 15; ++tick_count) {
        printf("Tick %d: ", tick_count);
        tick();
    }

    clear_timers();
    return 0;
}


// 요약해보자면
// 타이머를 등록하고
// 시간이 흐를 때마다 head의 시간만 감소하고
// head의 시간이 0이되면 콜백 실행후 제거한다.

// 리스트에는 실제 시간이 아닌 앞 타이머와의 시간차이를 저장하고
// 매 tick마다 모든 타이머가 아닌 맨 앞만 감소시킨다
// timer_head 요거 하나가 모든 타이머의 시간차이를 계산해서 
// 타이머 리스트에 시작점을 가리키고 있다가
// 순서대로 0이되면 해당 타이머를 만료시키고 다음 노드의 헤드로 넘어가는 식이다

// delta time은 타이머하나의 만료시간이 아닌 만료시간이 빠른 순서로 그다음 순서의 만료시간을 뺀만큼씩만 값이 들어가있게된다.