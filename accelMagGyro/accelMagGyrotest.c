#include <stdio.h>
#include <unistd.h>
#include "accelMagGyro.h"

#define ACCEL_THRESHOLD 5000
#define FORWARD_THRESHOLD 4000

int main(void)
{
    int first_accel[3];
    int second_accel[3];

    printf("Set Default Value\n");
    getAccel(first_accel);

    while (1) {
        getAccel(second_accel);

        // 오른쪽으로 기운 경우
        if (first_accel[0] - second_accel[0] > ACCEL_THRESHOLD) {
            printf("Char Go Right\n");
        }
        // 왼쪽으로 기운 경우
        else if (second_accel[0] - first_accel[0] > ACCEL_THRESHOLD) {
            printf("Char Go Left\n");
        }
        // 앞으로 기운 경우
        else if (second_accel[2] - first_accel[2] > FORWARD_THRESHOLD) {
            printf("Char Go Foward\n");
        }
        // 뒤로 기운 경우
        else if (first_accel[2] - second_accel[2] > FORWARD_THRESHOLD) {
            printf("Char Go Backward\n");
        }
        // 아무 동작 없으면
        else {
            printf("Stable\n");
        }

        // 기준값 업데이트
        for (int i = 0; i < 3; i++) {
            first_accel[i] = second_accel[i];
        }
        sleep(1); // 1초 대기
    }

    return 0;
}
