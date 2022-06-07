#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/uio.h>

#include "locker.h"


class http_conn {
public:
    static int m_epollfd;
    static int m_user_count;
    
    http_conn() {}

    ~http_conn() {}

    void process();

private:
    int m_socket;
    sockaddr_in m_address;
};

#endif