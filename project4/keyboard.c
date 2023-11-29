#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 1024 // 타이핑 최대 길이

// 잘못 타이핑 계산
int miss(const char *origin, const char *typing) {
    int mistakes = 0;
    while (*origin != '\0' && *typing != '\0') {
        if (*origin != *typing) {
            mistakes++; //문자 다르면 ++
        }
        origin++;
        typing++;
    }
    return mistakes + strlen(origin) - strlen(typing); // 실수 값 반환
}

int main() {
    char origin[MAX_LENGTH]; // 문장 저장
    char typing[MAX_LENGTH]; // 입력 문장 저장
    int checkMistakes = 0; // 실행 수
    int sentence; // 문장 수
    int i; // count
    time_t startTime, endTime; //시작, 종료 시간
    double totalTime = 0;
    int totalChars = 0;

    printf("입력 할 문장 수.. : ");
    scanf("%d", &sentence);
    getchar(); // 버퍼 비우기

    for (i = 0; i < sentence; i++) {
        printf("입력 할 문장.. :\n");
        fgets(origin, MAX_LENGTH, stdin);
        origin[strcspn(origin, "\n")] = 0;

        printf("입력 시작.. :\n");
        startTime = time(NULL);
        fgets(typing, MAX_LENGTH, stdin);
        typing[strcspn(typing, "\n")] = 0; 
        endTime = time(NULL);

        checkMistakes += miss(origin, typing);
        totalTime += difftime(endTime, startTime);
        totalChars += strlen(typing);
    }

    double speed = totalChars / totalTime * 60;

    printf("타이핑 실수.. : %d\n", checkMistakes);
    printf("타이핑 속도.. : %.2f characters per minute\n", speed);

    return 0;
}
