/**
 * @file pipe_t.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*
#include <unistd.h>
int pipe(int pipefd[2]);
    功能：创建一个匿名管道，用来进程间通信。
    参数：int pipefd[2] 这个数组是一个传出参数。
        pipefd[0] 对应的是管道的读端
        pipefd[1] 对应的是管道的写端
    返回值：
        成功 0
        失败 -1

    管道默认是阻塞的：如果管道中没有数据，read阻塞，如果管道满了，write阻塞

    注意：匿名管道只能用于具有关系的进程之间的通信（父子进程，兄弟进程）
*/
 
 // 子进程发送数据给父进程，父进程读取到数据输出
#include <sched.h>
#include <unistd.h>

#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {

    // 创建pipe
    int pipefd[2];
    int ret = pipe(pipefd);
    if (ret == -1) {
        perror("pipe");
        exit(0);
    }

    // 创建子进程
    pid_t pid = fork();
    if (pid > 0) { //parent
        printf("parent-%d ",getpid());
        
        // close(pipefd[1]); 只读情况下，可以关闭写端
        char buf[1024] = {0};

        while (true) {
            int ret = read(pipefd[0], buf, sizeof(buf));
            printf("parent recv: %s \n", buf);

            char * str = "hi, i am parent";
            write(pipefd[1], str, strlen(str));
            sleep(1); // 避免
        }

    } else if (pid == 0) { //child
        // sleep(1);
        // close(pipefd[0]);
        printf("child-%d ",getpid());
        char buf[1024] = {0};
        while (true) {
            char *str = "hello, i am child \n";

            write(pipefd[1], str, strlen(str));
            // sleep(1); 避免child 直接将数据读出来，此时sleep 让CPU 执行 parent 逻辑取出数据 

            int len = read(pipefd[0], buf, sizeof(buf));
            printf("child recv: %s \n", buf);

            memset(buf, 0, sizeof(buf));
        }

    }


    return 0;
}