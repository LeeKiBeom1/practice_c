/*
Checksum 계산 (XOR 방식)
입력: 바이트 배열 [0x01, 0x02, 0x03, 0x04], 길이
출력: XOR 누적 체크섬 값
제약조건: 포인터 연산 사용.
실행결과: 

=== Day 7: XOR Checksum Calculation ===

[TX] Sending Packet...
     Data: 0x01 0x04 0x10 0x20 0x30 0x40 
     Calculated Checksum: 0x45

[RX] Receiving Normal Packet...
     >> Verification SUCCESS (Result: 0x00)

[RX] Receiving Corrupted Packet (Noise injected)...
     Corrupted Data: 0x01 0x04 0xEF 0x20 0x30 0x40 0x45
     >> Verification FAIL (Result: 0xFF)
     >> Error detected! Discarding packet.
     */


/*

# XOR의 특징 1-1

A XOR B XOR B = A
B XOR B = 0
A XOR 0 = A

1001
1001 -> 0000

1001
0000 -> 1001

# XOR의 특징 1-2

0x01 XOR 0x02 XOR 0x03 = 0x00

먼저 0x01 XOR 0x02 하면
0001
0010 -> 0011(= 0x03)

0x03 XOR 0x03 = 0x00

# 위와 같은 XOR의 성질을 활용해서 체크섬의 핵심 로직을 만들 수 있다.

*/

#include <stdio.h>
#include <stdint.h>

// 데이터들의 체크섬 값을 만드는 함수
uint8_t xor_checksum(uint8_t *data, int length)
{
    uint8_t checksum = 0;

    for (int i = 0; i < length; i++)
    {
        checksum ^= *(data + i);
    }

    return checksum;
}

int main(void)
{
    uint8_t data[] = {
        0x01,
        0x04,
        0x10,
        0x20,
        0x30,
        0x40
    };

    int length = sizeof(data) / sizeof(data[0]);

    uint8_t checksum = xor_checksum(data, length);
    // 데이터 송신하기전 체크섬 값을 계산하고 저장

    printf("=== Day 7: XOR Checksum Calculation ===\n\n");

    printf("[TX] Sending Packet...\n");
    printf("     Data: ");

    for (int i = 0; i < length; i++)
    {
        printf("0x%02X ", *(data + i));
    }

    printf("\n");
    printf("     Calculated Checksum: 0x%02X\n", checksum);


    // 정상 패킷의 경우
    uint8_t packet[] = {
        0x01,
        0x04,
        0x10,
        0x20,
        0x30,
        0x40,
        0x45
    };

    // 받은데이터의 크기부터 구하고
    int packet_length =
        sizeof(packet) / sizeof(packet[0]);
    // 마지막값을 제대로 체크섬 값을 보냈다면 0x00이 나와야 정상
    uint8_t result =
        xor_checksum(packet, packet_length);


    printf("\n\n[RX] Receiving Normal Packet...\n");

    if (result == 0)
    {
        printf("     >> Verification SUCCESS (Result: 0x%02X)\n",
               result);
    }
    else
    {
        printf("     >> Verification FAIL (Result: 0x%02X)\n",
               result);
    }


    // 손상된 패킷
    uint8_t corrupted_packet[] = {
        0x01,
        0x04,
        0xEF,   // 원래 0x10
        0x20,
        0x30,
        0x40,
        0x45
    };

    int corrupted_length =
        sizeof(corrupted_packet) / sizeof(corrupted_packet[0]);

    uint8_t corrupted_result =
        xor_checksum(corrupted_packet, corrupted_length);


    printf("\n\n[RX] Receiving Corrupted Packet (Noise injected)...\n");
    printf("     Corrupted Data: ");

    for (int i = 0; i < corrupted_length; i++)
    {
        printf("0x%02X ", *(corrupted_packet + i));
    }

    printf("\n");

    if (corrupted_result == 0)
    {
        printf("     >> Verification SUCCESS (Result: 0x%02X)\n",
               corrupted_result);
    }
    else
    {
        printf("     >> Verification FAIL (Result: 0x%02X)\n",
               corrupted_result);

        printf("     >> Error detected! Discarding packet.\n");
    }

    return 0;
}

/*

XOR연산자는 아주 간단한 기능을 가지고있어서 과연 이게 뭘 할 수 있나 싶지만
이를 활용하면 비트들이 일정한 패턴을 가지게끔 만들 수 있고 더 나아가 이 패턴을 활용하니까
데이터 통신을 하면서 일어날 수 있는 비정상 데이터를 체크하여
받은 데이터의 무결성 검사를 할 수 있게 되었다.

아주 작은 논리부터 시작하여 점점 확장되고 활용하는걸 배우면서
아주 신기하고 이렇게 만들어 냈다는게 참 대단한 것 같다.

*/
