#include <unistd.h>
#include <stdio.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {

    int fd = open("create_test.c", O_RDONLY);
    if (fd == -1) perror("open");

    int d_fd = open("copy.txt", O_WRONLY | O_CREAT, 0664);
    if (d_fd == -1) perror("create");

    char buff[1024] = {0};
    int len = 0;

    while ((len = read(fd, buff, sizeof(buff))) > 0 ) {
        write(d_fd, buff, len);
    }

    return 0;
}
