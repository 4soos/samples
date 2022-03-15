#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdio.h>
/*

标准 C 库函数
#include <stdio.h>
int fseek(FILE *stream, long offset, int whence);


Linux 系统函数
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);


作用：
1. 移动到文件起点
2. 获取当前文件指针位置
3. 获取文件长度
4. 拓展文件长度

*/

int main() {

    int fd = open("copy.d", O_RDWR );
    if (fd == -1) perror("open");

    int ret = lseek(fd, 100, SEEK_END);
    if (ret == -1) perror("open");

    write(fd, "\\n ", 100);

    return 0;
}