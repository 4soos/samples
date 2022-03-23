
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

int main() {

    int ret = access("chatb", F_OK);
    if (ret == -1) {
        printf("no chat file");
        ret = mkfifo("chata", 0664);
        if (ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    ret = access("chata", F_OK);
    if (ret == -1) {
        printf("no chat file");
        ret = mkfifo("chata", 0664);
        if (ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    // chata
    int fdw = open("chata", O_WRONLY);
    if (fdw == -1) {
        perror("open");
    }
    printf("open chata");


    int fdr = open("chatb", O_RDONLY);
    if (fdr == -1) {
        perror("open");
    }
    printf("open chatb");

    char buf[128];
    while (true) {
        memset(buf, 0, 128);
        fgets(buf, 128, stdin);
        
        ret = write(fdw, buf, strlen(buf));
        if (ret == -1) {
            perror("write");
            break;
        }

        memset(buf, 0, 128);
        int ret =read(fdr, buf, strlen(buf));
        if (ret <= 0) {
            perror("write");
            break;
        }

        printf("buf: %s \n", buf);
    }

    close(fdr);
    close(fdw);

    return 0;
}
