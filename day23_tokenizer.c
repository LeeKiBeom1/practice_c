#include <stddef.h>  // size_t
#include <stdio.h>   // printf

#define TOKEN_BUFFER_SIZE 64

// 원본 문자열을 수정하지 않는 간단한 문자열 토크나이저
// 첫 호출에는 문자열을 전달하고, 다음 호출부터는 NULL을 전달한다.
const char *safe_strtok(const char *string, char delimiter) {
    // const current 이것도 수정을 하는게 아닌 읽을뿐 읽어서 토큰에 복사하는 형태
    static const char *current = NULL;
    // 토큰도 static배열 이므로 하나의 토큰을 읽고 다음 토큰을 읽으면
    // 이전 토큰 내용은 새값으로 덮어 써진다.
    static char token[TOKEN_BUFFER_SIZE];

    // 새 문자열이 들어오면 탐색 위치를 문자열의 시작점으로 초기화한다.
    if (string != NULL) {
        current = string;
    }

    if (current == NULL) {
        return NULL;
    }

    // 구분자가 나올 때까지 계속 진행
    while (*current == delimiter) {
        current++;
    }

    // 더 이상 읽을 문자가 없으면 토큰 처리를 끝낸다.
    if (*current == '\0') {
        current = NULL;
        return NULL;
    }

    size_t token_length = 0;

    // 모든 가드문을 통과하고 나면 토큰 복사 진행
    // 구분자 또는 문자열의 끝을 만날 때까지 한 글자씩 복사한다.
    while (*current != '\0' && *current != delimiter) {
        // 토큰 버퍼의 공간 먼저 확인  - 1 해준 이유는 마지막 한칸에 '\0' 을 넣어줘야 해서
        if (token_length < TOKEN_BUFFER_SIZE - 1) {
            token[token_length++] = *current;
        }
        current++;
    }

    token[token_length] = '\0';

    // 구분자를 만났다면 다음 토큰의 시작 위치로 한 칸 이동한다.
    if (*current == delimiter) {
        current++;
    } else {
        current = NULL;
    }

    return token;
}

int main(void) {
    const char input[] = "GPS,37.5665,126.9780,20260213";
    const char delimiter = ',';

    printf("=== Day 23: Safe String Tokenizer (static) ===\n\n");
    printf("Input Data: \"%s\"\n", input);
    printf("Delimiter : '%c'\n\n", delimiter);

    // input은 current에 기억되었다.
    // token 포인터 주소를 받았다.
    const char *token = safe_strtok(input, delimiter);
    int token_number = 1;

    while (token != NULL) {
        printf("Token %d: %s\n", token_number, token);
        token_number++;
        // 새 문자열을 안주고 기존 문자열에서 다음토큰을 찾아서 줘라 라는뜻
        token = safe_strtok(NULL, delimiter);
        // 토큰이 null이 될때까지 반복해서 출력하게됨
    }

    printf("\n>> Original string check: \"%s\"\n", input);
    printf(">> (Original string remains unmodified)\n");

    return 0;
}
