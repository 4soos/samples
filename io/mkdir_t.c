 /*
  2     #include <sys/stat.h>
  3     #include <sys/types.h>
  4     int mkdir(const char *pathname, mode_t mode);
  5         作用：创建一个目录
  6         参数：
  7             pathname: 创建的目录的路径
  8             mode: 权限，八进制的数
  9         返回值：
 10             成功返回0， 失败返回-1
 11 
 */
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    char buf[128];

    getcwd(buf, sizeof(buf)); 
    printf(" %s \n" , buf);

    int ret = mkdir("./test1",  750);
    ret = rename("./test", "./rtest");

    ret = chdir("../");

    getcwd(buf, sizeof(buf)); 
    printf(" %s \n" , buf);


    return 0;
}
