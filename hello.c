#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

    int num;
    sscanf(argv[1], "%d", &num);
    printf("words: %d, file: %s\n", num, argv[2]);
    int fd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IRGRP|S_IROTH);
    for (int i = 0; i < num; ++i) {
        int word;
        read(0, &word, sizeof(word));
        write(fd, &word, sizeof(word));
    }
    close(fd);
    return 0;
}
