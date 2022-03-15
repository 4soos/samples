#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {

    ssize_t fd = open("creat.txt", O_RDWR | O_CREAT, 0777);

    if (fd == 01) perror("open");

    close(fd);

    return 0;
}

