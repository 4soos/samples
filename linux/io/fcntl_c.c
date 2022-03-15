
// NAME
//        fcntl - manipulate file descriptor
// SYNOPSIS
//        #include <fcntl.h>
//        int fcntl(int fd, int cmd, ... //* arg */ )
//         参数：
//             fd : 表示需要操作的文件描述符
//             cmd: 表示对文件描述符进行如何操作
//                 - F_DUPFD : 复制文件描述符,复制的是第一个参数fd，得到一个新的文件描述符（返回值）
//                     int ret = fcntl(fd, F_DUPFD);
//     
//                 - F_GETFL : 获取指定的文件描述符文件状态flag
//                   获取的flag和我们通过open函数传递的flag是一个东西。
//     
//                 - F_SETFL : 设置文件描述符文件状态flag
//                   必选项：O_RDONLY, O_WRONLY, O_RDWR 不可以被修改
//                   可选性：O_APPEND, O)NONBLOCK
//                     O_APPEND 表示追加数据
//                     NONBLOK 设置成非阻塞


#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <fcntl.h>

int main() {

    // 复制文件描述符
    // int fd = open("1.txt", O_RDONLY|O_CREAT);
    // int ret = fcntl(fd, F_DUPFD);
    // printf("ret %d ", ret);

    int m_fd = open("2.txt", O_RDWR|O_CREAT);
    char * str1 = "1111";
    write(m_fd, str1, strlen(str1));
    

    int flag = fcntl(m_fd, F_GETFL);
    flag |= O_APPEND;

    int ret2 = fcntl(m_fd, F_SETFL, flag);
    if (ret2 == -1) return -1;

    char * str = "Hello";
    write(m_fd, str, strlen(str));
    close(m_fd);

    return 0;
}

