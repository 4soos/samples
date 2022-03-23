/**
 * @file wait_pid.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-18
 * 
 * @copyright Copyright (c) 2022
  2     #include <sys/types.h>
  3     #include <sys/wait.h>
  4     pid_t waitpid(pid_t pid, int *wstatus, int options);
  5         功能：回收指定进程号的子进程，可以设置是否阻塞。
  6         参数：
  7             - pid:
  8                 pid > 0 : 某个子进程的pid
  9                 pid = 0 : 回收当前进程组的任意子进程    
 10                 pid = -1 : 回收任意的子进程，相当于 wait()  （最常用）
 11                 pid < -1 : 某个进程组的组id的绝对值，回收指定进程组中的子进程
 12             - options：设置阻塞或者非阻塞
 13                 0 : 阻塞
 14                 WNOHANG : 非阻塞
 15             - 返回值：
 16                 > 0 : 返回子进程的id
 17                 = 0 : options=WNOHANG, 表示还有子进程或者
 18                 = -1 ：错误，或者没有子进程了
 */

#include <sys/wait.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    
    pid_t pid;

    for (int i = 0; i < 5; i++) {
        pid = fork();

        if (pid == 0) break;
    }

    //parent
    if (pid > 0) {
        while (true) {
            sleep(1);
            printf("parent %d \n", getpid());

            int st;
            // int ret = waitpid(-1, &st, 0);
            int ret = waitpid(-1, &st, WNOHANG);

            if (ret == -1) break;

            if (ret == 0) continue; // 存在child process

            if (ret > 0) {
                if (WIFEXITED(st)) printf("exit status %d \n", WEXITSTATUS(st));

                if (WIFSIGNALED(st)) printf("signaled status %d \n", WTERMSIG(st));

                printf("child die,pid %d \n", ret);
            }

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
