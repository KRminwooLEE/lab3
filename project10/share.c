#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define SHM_NAME "shared_memory"
#define SEM_NAME "semaphore"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용: %s <source file> <destination file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *source_file = argv[1];
    const char *destination_file = argv[2];
    int source_fd, destination_fd, shm_fd;
    char *shared_memory;
    sem_t *semaphore;

    source_fd = open(source_file, O_RDONLY);
    if (source_fd == -1) {
        perror("소스파일 오픈 실패");
        exit(EXIT_FAILURE);
    }

    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 1024);
    shared_memory = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("공유 메모리 실패");
        exit(EXIT_FAILURE);
    }

    semaphore = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if (semaphore == SEM_FAILED) {
        perror("세마포어 열기 실패");
        exit(EXIT_FAILURE);
    }

    if (fork() == 0) {
        destination_fd = open(destination_file, O_WRONLY | O_CREAT, 0666);
        while (1) {
            sem_wait(semaphore);
            if (shared_memory[0] == '\0') {
                sem_post(semaphore);
                break;
            }
            write(destination_fd, shared_memory, strlen(shared_memory));
            shared_memory[0] = '\0';
            sem_post(semaphore);
        }
        close(destination_fd);
    } else {
        char buffer[1024];
        while (read(source_fd, buffer, 1024) > 0) {
            sem_wait(semaphore);
            strncpy(shared_memory, buffer, 1024);
            sem_post(semaphore);
        }
        sem_wait(semaphore);
        shared_memory[0] = '\0';
        sem_post(semaphore);

        close(source_fd);
    }

    munmap(shared_memory, 1024);
    close(shm_fd);
    shm_unlink(SHM_NAME);
    sem_close(semaphore);
    sem_unlink(SEM_NAME);

    return 0;
}
