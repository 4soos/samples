
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {

    // 映射文件
    int fd = open("mmap_t.c", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(0);
    }
    int len = lseek(fd, 0, SEEK_END);

    // 新文件
    int fd1 = open("cpy", O_RDWR|O_CREAT, 0664);
    if (fd1 == -1) {
        perror("open");
        exit(0);
    }

    truncate("cpy.txt", len); //扩展文件

    write(fd1, " ", 1);

    // 内存映射
    void *ptr = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    void *ptr1 = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED, fd1, 0);

    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(0);
    }
    if (ptr1 == MAP_FAILED) {
        perror("mmap");
        exit(0);
    }

    // 内存拷贝
    printf("content : %s", &ptr);
    memcpy(ptr1, ptr, len);

    // 释放
    munmap(ptr1, len);
    munmap(ptr, len);

    close(fd1);close(fd);

    return 0;
}

