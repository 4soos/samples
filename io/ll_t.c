
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <unistd.h>

#include <pwd.h>
#include <grp.h>
#include <time.h>

#include <string.h>

int main(int argc, char * argv[]) {

    struct stat file_data;

    if (argc < 2) {
       printf("%s filename\n", argv[0]);
       return -1; 
    }

    struct stat info;

    int ret = stat(argv[1], &info);// 获取文件信息

    if (ret == -1) {
        perror("open file");
        return -1;
    }
// #define S_IFMT  00170000
// #define S_IFSOCK 0140000
// #define S_IFLNK	 0120000
// #define S_IFREG  0100000
// #define S_IFBLK  0060000
// #define S_IFDIR  0040000
// #define S_IFCHR  0020000
// #define S_IFIFO  0010000
// #define S_ISUID  0004000
// #define S_ISGID  0002000
// #define S_ISVTX  0001000
    char perms[11] = {0}; // 保存文件类型
    switch (info.st_mode & S_IFMT) {
    // case S_ISVTX:
    //     perms[0] = 's';
    //     break;
    case S_IFLNK:
        perms[0] = 'l';
        break;
    case S_IFDIR:
        perms[0] = 'd';
        break;
    case S_IFREG:
        perms[0] = '-';
        break;
    case S_IFBLK:
        perms[0] = 'b';
        break;
    case S_IFCHR:
        perms[0] = 'c';
        break;
    case S_IFSOCK:
        perms[0] = 's';
        break;
    case S_IFIFO:
        perms[0] = 'p';
        break;
    default:
        perms[0] = '?';
        break;
    }

    // 文件所有者
    perms[1] = (info.st_mode & S_IRUSR) ? 'r':'-';
    perms[2] = (info.st_mode & S_IWUSR) ? 'w':'-';
    perms[3] = (info.st_mode & S_IXUSR) ? 'x':'-';

    // 文件所在组
    perms[4] = (info.st_mode & S_IRGRP) ? 'r':'-';
    perms[5] = (info.st_mode & S_IWGRP) ? 'w':'-';
    perms[6] = (info.st_mode & S_IXGRP) ? 'x':'-';

    // others
    perms[7] = (info.st_mode & S_IROTH) ? 'r':'-';
    perms[8] = (info.st_mode & S_IWOTH) ? 'w':'-';
    perms[9] = (info.st_mode & S_IXOTH) ? 'x':'-';

    int link_num = info.st_nlink;
    char * file_user = getpwuid(info.st_uid)->pw_name;
    char * file_grp = getgrgid(info.st_gid)->gr_name;

    long int size = info.st_size;

    char * time = ctime(&info.st_mtime);
    char printbuf[1024];

    char mytime[512] = {0};
    strncpy(mytime, time, strlen(time) - 1);

    sprintf(printbuf, "%s %d %s %s %s %s", 
            perms, 
            link_num,
            file_user,
            file_grp,
            mytime,
            argv[1]
        );
    
    printf("%s \n", printbuf);

    return 0;
}
