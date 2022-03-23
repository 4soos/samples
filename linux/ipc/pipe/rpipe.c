#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>

int main() {

    int fd = open("fifo1", O_RDONLY);
    if (fd == -1) {
        perror("open fifo1");
        exit(0);
    }

    while (1) {
        char buf[1024] = {0};
        int len = read(fd, buf, sizeof(buf));
        if (len == 0) {
            printf("const char *, ...");
            break;
        }
        printf("recv buf: %s", buf);
    }

    close(fd);

    return 0;
}
