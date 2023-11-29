#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>

#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024
#define MSG_STOP    "exit"

int main(int argc, char **argv) {
    mqd_t mq;
    char buffer[MAX_SIZE];

    mq = mq_open(QUEUE_NAME, O_WRONLY);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }

    printf("메시지를 입력하세요 : ");
    while (fgets(buffer, MAX_SIZE, stdin) != NULL) {
        if (mq_send(mq, buffer, strlen(buffer), 0) == -1) {
            perror("mq_send");
            continue;
        }

        if (!strncmp(buffer, MSG_STOP, strlen(MSG_STOP))) {
            break;
        }

        printf("메시지를 입력하세요 : ");
    }

    mq_close(mq);

    return 0;
}
