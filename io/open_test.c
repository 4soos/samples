#include <stdio.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <unistd.h>

int main() {

    // 打开一个已经存在的文件
    int fd = open("a.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
    }
    close(fd);

    // 新建文件

    return 0;
}

