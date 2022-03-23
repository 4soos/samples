/**
 * @file wait_t.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-18
 * 
 * @copyright Copyright (c) 2022
 * 
  2     #include <sys/types.h>
  3     #include <sys/wait.h>
  4     pid_t wait(int *wstatus);
  5         功能：等待任意一个子进程结束，如果任意一个子进程结束了，次函数会回收子进程的资源。
  6         参数：int *wstatus
  7             进程退出时的状态信息，传入的是一个int类型的地址，传出参数。
  8         返回值：
  9             - 成功：返回被回收的子进程的id
 10             - 失败：-1 (所有的子进程都结束，调用函数失败)
 11 
 12     调用wait函数的进程会被挂起（阻塞），直到它的一个子进程退出或者收到一个不能被忽略的信号时才被唤醒（相当于继续往下执行
 13     如果没有子进程了，函数立刻返回，返回-1；如果子进程都已经结束了，也会立即返回，返回-1.

# define WEXITSTATUS(status)	__WEXITSTATUS (status)
# define WTERMSIG(status)	__WTERMSIG (status)
# define WSTOPSIG(status)	__WSTOPSIG (status)
# define WIFEXITED(status)	__WIFEXITED (status)
# define WIFSIGNALED(status)	__WIFSIGNALED (status)
# define WIFSTOPPED(status)	__WIFSTOPPED (status)

*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

int main() {

    pid_t pid;

    for (int i = 0; i < 5; i++) {
        pid = fork();

        if (pid == 0) break;
    }

    if (pid > 0) {
        while (true) {
            printf("parent %d \n", getpid());
            // 不获取子进程推出状态
            // int ret = wait(NULL);
            // printf("child die,pid %d \n", ret);
            // sleep(1);

            int st;
            int ret = wait(&st);

            if (ret == -1) break;

            if (WIFEXITED(st)) printf("exit status %d \n", WEXITSTATUS(st));

            if (WIFSIGNALED(st)) printf("signaled status %d \n", WTERMSIG(st));


            printf("child die,pid %d \n", ret);

            sleep(1);
        }
    //chlid
    } else if (pid == 0) {
        while (true) {
            printf("child pid = %d \n", getpid());
            sleep(1);
        }
        exit(0);
    }

    return 0;
}