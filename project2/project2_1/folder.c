#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    DIR *dir;
    struct dirent *entry;

    if (mkdir(testf, 0755) < 0) {
        perror("mkdir");
        exit(1);
    }

    if ((dir = opendir(dirname)) != NULL) {
        printf("Directory contents:\n");
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }
        closedir(dir);
    } else {
        perror("opendir");
    }

    if (rmdir(dirname) < 0) {
        perror("rmdir");
        exit(1);
    }

    return 0;
}
