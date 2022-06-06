#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/socket.h>

struct sock_info {
    int fd;
    pthread_t tid;
    struct sockaddr_in addr;
};

struct sock_info sockinfos[1024];

void* working(void *arg) {
// 子线程和客户端通信   cfd 客户端的信息 线程号
    // 获取客户端的信息
    struct sockInfo * pinfo = (struct sockInfo *)arg;

    char cliIp[16];
    inet_ntop(AF_INET, &pinfo->addr.sin_addr.s_addr, cliIp, sizeof(cliIp));
    unsigned short cliPort = ntohs(pinfo->addr.sin_port);
    printf("client ip is : %s, prot is %d\n", cliIp, cliPort);

    // 接收客户端发来的数据
    char recvBuf[1024];
    while(1) {
        int len = read(pinfo->fd, &recvBuf, sizeof(recvBuf));

        if(len == -1) {
            perror("read");
            exit(-1);
        }else if(len > 0) {
            printf("recv client : %s\n", recvBuf);
        } else if(len == 0) {
            printf("client closed....\n");
            break;
        }
        write(pinfo->fd, recvBuf, strlen(recvBuf) + 1);
    }
    close(pinfo->fd);
    return NULL;
}

int main() {

    //  创建socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    if (lfd == -1) {
        perror("socket");
        exit(-1);
    }
    
    // 绑定
    struct sockaddr_in saddr = {
        .sin_family = AF_INET,
        .sin_port = htons(9999),
        .sin_addr.s_addr = INADDR_ANY
    };
    int ret = bind(lfd, (struct sockaddr *) &saddr, sizeof(saddr));
    if (ret == -1) {
        perror("bind");
        exit(-1);
    }

    // 监听
    ret = listen(lfd, 128);
    if (ret == -1) {
        perror("listen");
        exit(-1);
    }

    int max = sizeof(sockinfos) / sizeof(sockinfos[0]);
    for (int i=0; i < max; i++) {
        bzero(&sockinfos[i], sizeof(sockinfos));
        sockinfos[i].fd = -1;
        sockinfos[i].tid = -1;
    }

    while (true) {
        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);

        int cfd = accept(lfd, (struct sockaddr*) &cliaddr, &len);
        pthread_t tid;

        struct sockinfo *pinfo;
        for (int i=0; i < max; i++) {
            // 查询可用 sockinfo
            if (sockinfos[i].fd == -1) {
                pinfo = &sockinfos[i];
                break;
            }

            if (i == max-1) {
                sleep(1);
                i--;
            }
        }

        pinfo->fd = cfd;
        memcpy(&pinfo->addr, &cliaddr, len);


        pthread_create(&tid, NULL, working, NULL);
        pthread_detach(pinfo->fd);
    }

    return 0;
}
