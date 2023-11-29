#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>

#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024
#define MSG_STOP    "exit"

int main(int argc, char **argv) {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE + 1];
    int must_stop = 0;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }

    do {
        ssize_t bytes_read;

        bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        if (bytes_read < 0) {
            perror("mq_receive");
            continue;
        }

        buffer[bytes_read] = '\0';
        if (!strncmp(buffer, MSG_STOP, strlen(MSG_STOP))) {
            must_stop = 1;
        } else {
            printf("클라이언트: %s\n", buffer);
        }
    } while (!must_stop);

    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}
