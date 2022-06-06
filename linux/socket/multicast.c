#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>


int udp_server_init(uint16_t port)
{
	int sockfd;

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		perror("socket");
		return -1;
	}


	struct sockaddr_in server_addr;

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    
    int opt = 1;

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt)) == -1)
	{
		close(sockfd);
		perror("SO_REUSEADDR");
		return -3;
	}


	if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		close(sockfd);
		perror("bind");
		return -2;
	}



	return sockfd;
}




void udp_test(void)
{
	//	创建一个 UDP 的搜索 服务 套接字

	int socket_fd;

	if ((socket_fd = udp_server_init(60002)) < 0)
	{
		printf("Create udp socket error[%d]\r\n", socket_fd);

		return;
	}

	//	加入多播组

	struct ip_mreq mreq;

	memset(&mreq, 0, sizeof(mreq));

	mreq.imr_multiaddr.s_addr = inet_addr("239.255.255.249");
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);


    int loop = 1;
    if( -1 == setsockopt(socket_fd,IPPROTO_IP, IP_MULTICAST_LOOP,&loop, sizeof(loop)))  // 允许内环
	{
		perror("IP_MULTICAST_LOOP"); // 设置失败也没关系
	}

	/* 把本机加入组播地址，即本机网卡作为组播成员，只有加入组才能收到组播消息 */
	if (setsockopt(socket_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(struct ip_mreq)) == -1)
	{
		perror("IP_ADD_MEMBERSHIP");
		pthread_exit(NULL);
	}else
	{
		printf("IP_ADD_MEMBERSHIP OK!\r\n");
	}

	int buffersize = 1024;
	if(setsockopt(socket_fd, SOL_SOCKET, SO_RCVBUF, &buffersize, sizeof(buffersize)) == -1) // 设置接收缓存
	{
		perror("SO_RCVBUF");
		pthread_exit(NULL);
	}

	socklen_t opt = 1;

	if (setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, (const void *)&opt, sizeof(opt)) == -1) // 允许广播
	{
		close(socket_fd);
		perror("SO_BROADCAST");
		pthread_exit(NULL);
	}

    fcntl(socket_fd, F_SETFL, fcntl(socket_fd, F_GETFL, 0) | O_NONBLOCK); // 设置为非阻塞IO

	while (1)
	{
		usleep(1000 * 10);

        uint8_t recv_buff[1024];
        struct sockaddr_in remote_addr;		//	远程地址
        socklen_t remote_addr_size = sizeof(remote_addr);
        
        //recvfrom(sockfd, recv_buff, sizeof(recv_buff), 0, addr, addr_len)
        if(recvfrom(socket_fd, recv_buff, sizeof(recv_buff), 0,  (struct sockaddr *)&remote_addr, &remote_addr_size) > 0)
        	printf("recv from %s， port %d\r\n", inet_ntoa(remote_addr.sin_addr), remote_addr.sin_port);
    }
}

int main(void)
{
    udp_test();
    return 0;
}




