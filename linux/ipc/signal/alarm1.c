#include <stdio.h>
#include <unistd.h>
#include <unistdio.h>

/** 
    实际时间 = 内核时间 + 用户时间 + 消耗时间
    进行IO 文件操作比较浪费时间

    定时器与当前程序没有关系
 */

int main() {

    alarm(1);
    int i = 0;

    while (1) {
        printf("%i \n", i++);
    }

    return 0;
}

