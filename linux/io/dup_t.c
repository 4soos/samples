/*
#include <unistd.h>
int dup(int oldfd);
    作用：复制一个新的文件描述符
    fd=3, int fd1 = dup(fd),
    fd指向的是a.txt, fd1也是指向a.txt
    从空闲的文件描述符表中找一个最小的，作为新的拷贝的文件描述符


   #include <unistd.h>
    int dup2(int oldfd, int newfd);
        作用：重定向文件描述符
        oldfd 指向 a.txt, newfd 指向 b.txt
        调用函数成功后：newfd 和 b.txt 做close, newfd 指向了 a.txt
        oldfd 必须是一个有效的文件描述符
        oldfd和newfd值相同，相当于什么都没有做
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

int main() {

    int fd = open("dup.txt", O_RDWR | O_CREAT, 0664);
    int fd_d = dup(fd);

    printf("fd %d fd_d %d", fd, fd_d);
    
    close(fd);

    char * str = "Hello dup!";

    write(fd_d, str, strlen(str));

    // dup2
    int fd1 = open("dup2.txt", O_RDWR|O_CREAT, 0664);
    int fd2 = open("dup3.txt", O_RDWR|O_CREAT, 0664);

    printf("fd1 %d fd2 %d \n\n\n", fd1, fd2);

    int fd3 = dup2(fd1, fd2);
    printf("fd3 %d fd1 %d fd2 %d", fd3, fd1, fd2);

    char * str1 = "Hello dup2";

    write(fd1, str, strlen(str));

    return 0;
}

