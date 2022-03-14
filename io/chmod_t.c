/*
#include <sys/stat.h>
int chmod(const char *pathname, mode_t mode);
    修改文件的权限
    参数：
        - pathname: 需要修改的文件的路径
        - mode:需要修改的权限值，八进制的数
    返回值：成功返回0，失败返回-1
*/

/*
#include <unistd.h>
#include <sys/types.h>
int truncate(const char *path, off_t length);
    作用：缩减或者扩展文件的尺寸至指定的大小
    参数：
        - path: 需要修改的文件的路径
        - length: 需要最终文件变成的大小
    返回值：
        成功返回0， 失败返回-1
*/


#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main() {

    int ret = chmod("copy.c", 0777);

    if (ret == -1) {
        perror("chmod");
        return -1;
    }

    ret = truncate("access_", 0);
    if (ret == -1) {
        perror("truncate");
        return -1;
    }

    return 0;
}
