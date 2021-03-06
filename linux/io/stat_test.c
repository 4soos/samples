#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdio.h>


/**
 * #include <sys/stat.h>    
 * int stat(const char *restrict path, struct stat *restrict buf);
 * -- path: 文件路径
 * -- buf: 结构体变量， 传出参数用于保存
 * -- return:
 *      - 0, 成功
 *      - -1, 失败， errno
 * 
 * 
 **/

// struct stat {
//     dev_t     st_dev;         /* ID of device containing file */
//     ino_t     st_ino;         /* Inode number */
//     mode_t    st_mode;        /* File type and mode */
//     nlink_t   st_nlink;       /* Number of hard links */
//     uid_t     st_uid;         /* User ID of owner */
//     gid_t     st_gid;         /* Group ID of owner */
//     dev_t     st_rdev;        /* Device ID (if special file) */
//     off_t     st_size;        /* Total size, in bytes */
//     blksize_t st_blksize;     /* Block size for filesystem I/O */
//     blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

//     /* Since Linux 2.6, the kernel supports nanosecond
//     precision for the following timestamp fields.
//     For the details before Linux 2.6, see NOTES. */

//     struct timespec st_atim;  /* Time of last access */
//     struct timespec st_mtim;  /* Time of last modification */
//     struct timespec st_ctim;  /* Time of last status change */

// #define st_atime st_atim.tv_sec      /* Backward compatibility */
// #define st_mtime st_mtim.tv_sec
// #define st_ctime st_ctim.tv_sec
// };


//  lstat() 获取软链接信息

int main() {

    struct stat statbuf;

    int ret = stat("open", &statbuf);

    if (ret == -1) {
        perror("stat");
        return -1;
    } 

    printf("size: %ld \n", statbuf.st_size);

    return 0;
}
