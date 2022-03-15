/**
 * @file fork_t.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-16
 * 
 * @copyright Copyright (c) 2022
 * 
```
#include <sys/types.h>
#include <unistd.h>

pid_t fork(void):
    创建子进程
    返回值:
        有两个返回值， 一个在父进程中， 一个在子进程中；
        父进程返回子进程的ID, 子进程返回0;
        父进程中返回值-1时，则创建失败
```
 */

#include <stdio.h>
#include <unistd.h>

int main() {

    pid_t pid = fork();
    printf("pid %d \n", pid);
    if (pid > 0) {
        // parent
        printf("parent %d %d \n", getpid(), getppid());

    } else if (pid == 0) {
        // child
        printf("child %d %d \n", getpid(), getppid());
    }

    for (int i = 0; i < 4; i++) {
        printf("i %d \n", i);
        sleep(1);
    }

    return 0;
}