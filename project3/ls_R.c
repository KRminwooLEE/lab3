#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void listDirectory(const char *basePath);
int checkabc(const void *a, const void *b);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    listDirectory(argv[1]);

    return EXIT_SUCCESS;
}

void listDirectory(const char *basePath) { //basePath에 지정된 디렉토리 내용
    char path[1000]; // 경로 저장
    char *names[1024]; // 이름 저장
    int count = 0; // 읽은 항목 수 체크

    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir) return;

    printf("%s:\n", basePath);

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            names[count] = strdup(dp->d_name); // 복사 및 저장
            count++;
        }
    }

    qsort(names, count, sizeof(char *), checkabc); //출력시 abc순서에 맞춤

    for (int i = 0; i < count; i++) {
        printf("%s ", names[i]);
    }
    printf("\n\n");
    // 재귀적으로 하위 디렉토리 탐색
    for (int i = 0; i < count; i++) {
        strcpy(path, basePath);
        strcat(path, "/");
        strcat(path, names[i]);

        struct stat path_stat;
        if (stat(path, &path_stat) == 0) {
            if (S_ISDIR(path_stat.st_mode)) {
                listDirectory(path);
            }
        }

        free(names[i]);
    }

    closedir(dir);
}

int checkabc(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

