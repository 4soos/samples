#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <unistd.h>

/*
#include <unistd.h>
int access(const char *pathname, int mode);
    作用：判断某个文件是否有某个权限，或者判断文件是否存在
    参数： 
        - pathname: 判断的文件路径
        - mode:
            R_OK: 判断是否有读权限
            W_OK: 判断是否有写权限
            X_OK: 判断是否有执行权限
            F_OK: 判断文件是否存在
    返回值：成功返回0， 失败返回-1
*/

int main() {

    int ret = access("./access_", R_OK | W_OK | X_OK | F_OK);

    if (ret == -1) {
        perror("access");
        return -1;
    } else {

    }

    return 0;
}