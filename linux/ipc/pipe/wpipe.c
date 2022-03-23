#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>

int main() {

    int ret = access("fifo1", F_OK);
    if (ret == -1) {
        perror("fifo1 not exit");
        int ret = mkfifo("fifo1", 0664);
        if (ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    int fd = open("fifo1", O_WRONLY);
    if (fd == -1) {
        perror("open fifo1");
        exit(0);
    }

    for (int i = 0; i < 100; i++) {
        char buf[1024];
        sprintf(buf, "hello %d \n", i);
        printf("write data: %s \n", buf);
        write(fd, buf, strlen(buf));
        sleep(1);
    }

    close(fd);

    return 0;
}
