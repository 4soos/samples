#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include <signal.h>
#include <wait.h>

__sighandler_t recycle_child(void) {
    while (true) {
        int ret = waitpid(-1, NULL, WNOHANG);
        if (ret == -1) {
            // 
            break;
        } else if (ret == 0) {
            break;
        } else if (ret > 0){
            printf("child process id %d recycle /n", ret);
        }
    }
}

int main() {

    struct sigaction act = {
        .sa_flags = 0,
        .sa_handler = recycle_child()
    };
    sigemptyset(&act.sa_mask);

    sigaction(SIGCHLD, &act, NULL);

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
        exit(0);
    }

    // 监听
    ret = listen(lfd, 5);
    if (ret == -1) {
        perror("listen");
        exit(-1);
    }

    while (true) {
        // 
        struct sockaddr_in caddr;
        int len = sizeof(caddr);
        
        int cfd = accept(lfd, (struct sockaddr *) &caddr, &len);
        if (cfd == -1) {
            perror("accpet");
            exit(-1);
        }

        pid_t pid = fork();
        if (pid == 0) { // child
            char cli_ip[16];
            inet_ntop(AF_INET, &caddr.sin_addr.s_addr, cli_ip, sizeof(cli_ip));
            unsigned short cli_port = ntohs(caddr.sin_port);
            printf("client ip is : %s port is %d", cli_ip, cli_port);

            char recv_buf[1024] = {0};
            while (true) {
                int len = read(cfd, &recv_buf, sizeof(recv_buf));
                if (len == -1) {
                    perror("read");
                    exit(-1);
                } else if (len > 0) {
                    printf("recv client data : %s \n", recv_buf);
                } else {
                    printf("client closed");
                }

                write(cfd, recv_buf, strlen(recv_buf));
            }

            close(cfd);
            exit(0); //  子进程退出
        }
    }
    close(lfd);

    return 0;   
}
