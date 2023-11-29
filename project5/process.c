#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t a;

    a = fork();

    if (a > 0) {
        printf("부모 프로세스 PID: %d\n", getpid());
        wait(NULL);
        printf("자식 프로세스가 종료됨\n");
    }
    else if (a == 0) {
        printf("자식 프로세스 PID: %d, 부모 PID: %d\n", getpid(), getppid());
        exit(0);
    }
    else {
        perror("fork 실패");
        exit(1);
    }

    return 0;
}
