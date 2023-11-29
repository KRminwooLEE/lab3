#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int myPipe[2];
    pid_t childpid;
    char readBuffer[100];
    char writeBuffer[] = "파이프 전달 성공.";

    if (pipe(myPipe) < 0) {
        perror("파이프 생성 실패");
        exit(1);
    }
    if ((childpid = fork()) < 0) {
        perror("프로세스 생성 실패");
        exit(1);
    }
    if (childpid == 0) {
        close(myPipe[1]);
        int bytes_read = read(myPipe[0], readBuffer, sizeof(readBuffer));
        if (bytes_read < 0) {
            perror("읽기 실패");
        } else {
            readBuffer[bytes_read] = '\0';
            printf("받은 메시지 : %s\n", readBuffer);
        }
        close(myPipe[0]);
    } else {
        close(myPipe[0]);
        if (write(myPipe[1], writeBuffer, strlen(writeBuffer) + 1) < 0) {
            perror("쓰기 실패");
        }
        close(myPipe[1]);
        wait(NULL);
    }

    return 0;
}
