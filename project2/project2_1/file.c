#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd;
    char buffer[1024];

    fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);

    printf("쓰기 : ");
    fgets(buffer, 1024, stdin);

    write(fd, buffer, strlen(buffer));

    close(fd);

    return 0;
}
