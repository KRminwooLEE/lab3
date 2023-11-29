#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main() {
    int n, i;
    char dirName[100], fileName[100], filePath[200];
    FILE *fp;
    DIR *d;

    printf("생성할 디렉터리 수: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("디렉터리 #%d 이름: ", i + 1);
        scanf("%s", dirName);
        if (mkdir(dirName, 0777) == -1) {
            perror("mkdir");
            return 1;
        }
    }

    printf("디렉터리 선택: ");
    scanf("%s", dirName);

    d = opendir(dirName);
    if (d == NULL) {
        perror("opendir");
        return 1;
    }

    printf("생성할 파일이름: ");
    scanf("%s", fileName);

    snprintf(filePath, sizeof(filePath), "%s/%s", dirName, fileName);

    fp = fopen(filePath, "w");
    if (fp == NULL) {
        perror("fopen");
        closedir(d);
        return 1;
    }

    printf("파일 '%s' 생성 완료.\n", filePath);

    fclose(fp);

    closedir(d);

    printf("삭제할 디렉터리 이름 (0 - 종료): ");
    scanf("%s", dirName);

    if (strcmp(dirName, "0") != 0) {
        if (rmdir(dirName) == -1) {
            perror("rmdir");
            return 1;
        }
        printf("디렉터리 '%s' 삭제 완료.\n", dirName);
    } else {
        printf("프로그램 종료.\n");
    }

    return 0;
}
