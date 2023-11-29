#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

void test_log(const char *message) {
    FILE *file = fopen("log.txt", "a");
    if (file == NULL) {
        perror("파일을 열 수 없습니다.");
        return;
    }

    time_t now;
    time(&now);
    char *time_string = ctime(&now);
    time_string[24] = '\0';

    fprintf(file, "[%s] %s\n", time_string, message);
    fclose(file);
}

void test_1(int sig) {
    printf("LOG 기록\n");
    test_log("Log를 기록합니다...");
}

int main() {
    signal(SIGUSR1, test_1);

    while (1) {
        printf("프로그램이 실행중입니다...\n");
        sleep(5);
    }

    return 0;
}

