#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <unistd.h>

int get_file_nums(const char * path);

int main(int argc, char * argv[]) {

    if (argc < 2) {
        printf("%s path\n", argv[0]);
        return -1;
    }

    int num = get_file_nums(argv[1]);

    printf("files number is : %d \n", num);


    return 0;
}

int get_file_nums(const char * path) {
    // 1.  打开目录
    DIR * dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        _exit(0);
    }
    
    struct dirent * ptr;

    // 文件个数
    int total = 0;

    while ((ptr = readdir(dir)) != NULL) {

        // 获取名称
        char * dname = ptr->d_name;

        // 忽略 `.` & `..` 
        if (strcmp(dname, ".") == 0 || strcmp(dname, "..") == 0) {
            continue;
        }

        // 判断是否是普通文件还是目录
        if (ptr->d_type == DT_DIR) {
            char new_path[256];

            // 继续读取当前目录
            sprintf(new_path, "%s/%s", path, dname);
            total += get_file_nums(new_path);
        }

        if (ptr->d_type == DT_REG) {
            total++;
        }
    }
    closedir(dir);
    
    return total;
}
