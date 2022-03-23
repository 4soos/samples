/**
 * @file execlp_t.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-18
 * 
 * @copyright Copyright (c) 2022
 * int execl(const char *path, const char *arg, ...);
 *      - path:
            程序名称 (从环境变量里面自己寻找)
        - arg:
            配合可执行文件的参数 (第一个参数大部分是程序本身，第二个开始才是实际需要的参数， 以NULL结尾)
        
        return:
            (失败的时候返回)-1, errno

l list
p path
v vector
e environment
 */

#include <unistd.h>

int main() {

    pid_t pid = fork();

    if (pid > 0) {
        printf("parent pid: %d", getpid());
        sleep(1);
    } else if (pid == 0) {
        // execl("a.out", "a.out", NULL);
        // printf("after execl");
    }
    printf("test");


    execlp("ip","ip", "-a", NULL);

    return 0;
}

