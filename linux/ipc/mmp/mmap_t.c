
/*
void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
    - 功能：将一个文件或者设备的数据映射到内存中
    - 参数：
        - void *addr: NULL, 由内核指定
        - length : 要映射的数据的长度，这个值不能为0。建议使用文件的长度。
                获取文件的长度：stat() lseek()
        - prot : 对申请的内存映射区的操作权限
            -PROT_EXEC ：可执行的权限
            -PROT_READ ：读权限
            -PROT_WRITE ：写权限
            -PROT_NONE ：没有权限
            要操作映射内存，必须要有读的权限。
            PROT_READ、PROT_READ|PROT_WRITE
        - flags :
            - MAP_SHARED : 映射区的数据会自动和磁盘文件进行同步，进程间通信，必须要设置这个选项
            - MAP_PRIVATE ：不同步，内存映射区的数据改变了，对原来的文件不会修改，会重新创建一个新的>
        - fd: 需要映射的那个文件的文件描述符
            - 通过open得到，open的是一个磁盘文件
            - 注意：文件的大小不能为0，open指定的权限不能和prot参数有冲突。
                prot: PROT_READ                open:只读/读写 
                prot: PROT_READ | PROT_WRITE   open:读写
        - offset：偏移量，一般不用。必须指定的是 4k 的整数倍，0表示不偏移。

    - 返回值：返回创建的内存的首地址
        失败返回MAP_FAILED，(void *) -1
int munmap(void *addr, size_t length);
    - 功能：释放内存映射
    - 参数：
        - addr : 要释放的内存的首地址
        - length : 要释放的内存的大小，要和mmap函数中的length参数的值一样。
*/

#include <sys/mman.h>
#include <sys/types.h>

#include <fcntl.h>
#include <sys/wait.h>
#include <wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main() {

    // 1.打开一个文件
    int fd = open("/home/young/my_repo/samples/linux/ipc/mmp/test.txt", O_RDWR);
    int size = lseek(fd, 0, SEEK_END);  // 获取文件的大小
    printf("fd: %d , size: %d \n", fd, size);

    // 2.创建内存映射区
    void *ptr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED) {
        perror("MAP_FAILED: mmap ");
        exit(0);
    }
    
    // 3.创建子进程
    pid_t pid = fork();
    if(pid > 0) {
        wait(NULL); 
        // 父进程
        char buf[64];
        strcpy(buf, (char *)ptr);
        printf("read data : %s\n", buf);

    }else if(pid == 0){
        // 子进程
        strcpy((char *)ptr, "nihao a, son!!!");
    }

    // 关闭内存映射区
    munmap(ptr, size);

    // TODO: 将fork 换成多 进程间通信

    return 0;
}
