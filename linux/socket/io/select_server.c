#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <string.h>
#include <stdbool.h>





int main() {

    int lfd = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in saddr;
    saddr.sin_port = htons(9999);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;

    bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));

    listen(lfd, 8);

    fd_set rdset;
    FD_ZERO(&rdset);
    FD_SET(lfd, &rdset);
    int maxfd = lfd;

    while (true) {
        // 调用 select
        int ret = select(maxfd+1, &rdset, NULL, NULL, NULL);
        if (ret == -1) {
            perror("select");
            return -1;
        } else if (ret == -1) {
            continue;
        } else if (ret > 0) {
            // 检测到了所有文件描述符的对应缓冲区的数据发生了改变
            if (FD_ISSET(lfd, &rdset)) {
                struct sockaddr_in cliaddr;
                int len = sizeof(cliaddr);
                int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);

                FD_SET(cfd, &rdset);

                maxfd = maxfd > cfd ? maxfd : cfd;
            }
            for (int i = lfd+1; i <= maxfd; i++) {
                if (FD_ISSET(i, &rdset)) {
                    // 对应的客户端发来了数据
                    char buf[1024] = {0};
                    int len = read(i, buf, sizeof(buf));
                    if (len == -1) {
                        perror("read");
                        exit(-1);
                    } else if (len == 0) {
                        printf("client closed ...\n");
                        close(i);
                    } else if (len > 0) {
                        printf("read buf = %s \n", buf);
                        write(i, buf, strlen(buf) + 1);
                    }
                }
            }
        }
    }

    close(lfd);

    return 0;
}






