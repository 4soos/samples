# SOCKET 编程

socket（套接字），就是对网络中不同主机上的应用进程之间进行双向通信的端点的抽象。

一个套接字就是网络上进程通信的一端，提供了应用层进程利用网络协议交换数据的机制。
从所处的地位来讲，套接字上联应用进程，下联网络协议栈，是应用程序通过网络协议进行通信的接口，
是应用程序与网络协议根进行交互的接口。

socket 可以看成是两个网络应用程序进行通信时，各自通信连接中的端点，这是一个逻辑上的概
念。它是网络环境中进程间通信的 API，也是可以被命名和寻址的通信端点，使用中的每一个套接
字都有其类型和一个与之相连进程。
通信时其中一个网络应用程序将要传输的一段信息写入它所在主机的 socket 中，该 socket 通过与网络接口卡（NIC）相连的传输介质将这段信息送到另外一台主机的 socket 中，使对方能够接收到这段信息。
socket 是由 IP 地址和端口结合的，提供向应用层进程传送数据包的机制。

socket 本身有“插座”的意思，在 Linux 环境下，用于表示进程间网络通信的特殊文件类型。
本质为内核借助缓冲区形成的伪文件。既然是文件，那么理所当然的，我们可以使用文件描述符引用套接字。
与管道类似的，Linux 系统将其封装成文件的目的是为了统一接口，使得读写套接字和读写文件的操作一致。
区别是管道主要应用于本地进程间通信，而套接字多应用于网络进程间数据的传递。

>套接字通信分两部分： 
>- 服务器端：被动接受连接，一般不会主动发起连接 
>- 客户端：主动向服务器发起连接 

>socket是一套通信的接口，Linux 和 Windows 都有，但是有一些细微的差别

## 字节序

现代 CPU 的累加器一次都能装载（至少）4 字节（这里考虑 32 位机），即一个整数。
那么这 4字节在内存中排列的顺序将影响它被累加器装载成的整数的值，这就是字节序问题。
在各种计算机体系结构中，对于字节、字等的存储机制有所不同，因而引发了计算机通信领域中一个很重要的问
题，即通信双方交流的信息单元（比特、字节、字、双字等等）应该以什么样的顺序进行传送。
如果不达成一致的规则，通信双方将无法进行正确的编码/译码从而导致通信失败。

字节序，顾名思义字节的顺序，就是大于一个字节类型的数据在内存中的存放顺序(一个字节的数据当然就无需谈顺序的问题了)。

字节序分为大端字节序（Big-Endian） 和小端字节序（Little-Endian）。
大端字节序是指一个整数的最高位字节（23～31 bit）存储在内存的低地址处，低位字节（0 ~ 7 bit）存储在内存的高地
址处；
小端字节序则是指整数的高位字节存储在内存的高地址处，而低位字节则存储在内存的低地址处

### 字节序举例
#### 小端字节序
`0x 01 02 03 04 - ff ` = 255

内存的方向 ----->

内存的低位 -----> 内存的高位

04 03 02 01

0x 11 22 33 44 12 34 56 78

```c
------------------------------------------->
|0x78 0x56 0x34 0x12 | 0x44 0x33 0x22 0x11 |
------------------------------------------->
内存地址增长方向
```

#### 大端字节序
`0x 01 02 03 04 `

内存的方向 ----->

内存的低位 -----> 内存的高位

01 02 03 04

0x 12 34 56 78 11 22 33 44

```c
------------------------------------------->
|0x12 0x34 0x56 0x78 | 0x11 0x22 0x33 0x44 |
------------------------------------------->
内存地址增长方向
```

网络字节顺序是 TCP/IP 中规定好的一种数据表示格式，它与具体的 CPU 类型、操作系统等无关，从而
可以保证数据在不同主机之间传输时能够被正确解释，网络字节顺序采用大端排序方式。

BSD Socket提供了封装好的转换接口，方便程序员使用。
- 从主机字节序到网络字节序的转换函数：htons、htonl；
- 从网络字节序到主机字节序的转换函数：ntohs、ntohl。

```c
h - host 主机，主机字节序 
to - 转换成什么 
n - network 网络字节序 
s - short unsigned short 
l - long unsigned int
```
```c
#include <arpa/inet.h> 
// 转换端口 
uint16_t htons(uint16_t hostshort); // 主机字节序 - 网络字节序 
uint16_t ntohs(uint16_t netshort); // 主机字节序 - 网络字节序 

// 转IP 
uint32_t htonl(uint32_t hostlong); // 主机字节序 - 网络字节序 
uint32_t ntohl(uint32_t netlong); // 主机字节序 - 网络字节序
```

### socket 地址
socket 地址是一个结构体，封装端口号和IP等信息。

#### 通用 socket 地址

socket 网络编程接口中表示 socket 地址的是结构体 sockaddr，其定义如下：

```c
#include <bits/socket.h> 
struct sockaddr { 
    sa_family_t sa_family; 
    char sa_data[14]; 
};

typedef unsigned short int sa_family_t;
```
`sa_family ` 成员是地址族类型（`sa_family_t`）的变量。
地址族类型通常与协议族类型对应。常见的协议族（protocol family，也称 domain）和对应的地址族入下所示：


|协议族    | 地址族    | 描述             |
| -     - |  -     - | -             - |
|PF_UNIX  | AF_UNIX  | UNIX本地域协议族  |
|PF_INET  | AF_INET  | TCP/IPv4协议族   |
|PF_INET6 | AF_INET6 | TCP/IPv6协议族   |

宏 `PF_*` 和 `AF_*` 都定义在 `bits/socket.h` 头文件中，且后者与前者有完全相同的值，所以二者通常混
用。

`sa_data` 成员用于存放 socket 地址值。但是，不同的协议族的地址值具有不同的含义和长度，如下所
示：

```c
| 协议族    | 地址值含义和长度                                                    |
| -        |   - -                                                              |     
| PF_UNIX  |文件的路径名，长度可达到108字节                                          |
| PF_INET  |16 bit 端口号和 32 bit IPv4 地址，共 6 字节                              |
| PF_INET6 |16 bit 端口号，32 bit 流标识，128 bit IPv6 地址，32 bit 范围 ID，共 26 字节 |

```
由上表可知，14 字节的 `sa_data` 根本无法容纳多数协议族的地址值。
因此，Linux 定义了下面这个新的通用的 socket 地址结构体，这个结构体不仅提供了足够大的空间用于存放地址值，而且是内存对齐的。

```c
#include <bits/socket.h> 

struct sockaddr_storage { 
    sa_family_t sa_family; 
    unsigned long int __ss_align; 
    char __ss_padding[ 128 - sizeof(__ss_align) ]; 
};

typedef unsigned short int sa_family_t;
```

#### 专用 socket 地址

很多网络编程函数诞生早于 IPv4 协议，那时候都使用的是 `struct sockaddr` 结构体，为了向前兼容，现
在 `sockaddr` 退化成了（void *）的作用，传递一个地址给函数，至于这个函数是 `sockaddr_in` 还是
`sockaddr_in6`，由地址族确定，然后函数内部再强制类型转化为所需的地址类型。


##  函数

```c
// server

// 1. 创建：fd
socket()

// 2. 绑定: ip, port
bind()

// 3. 监听： fd
listen()

// 4. 阻塞等待： 等待客户端发起连接
accept()

// 5. 通信
recv()
send()

// 6. 断开连接
close()

// ================================================

// client
// 1. 创建： fd
socket()

// 2. 连接： ip, port
connect()

// 3. 通信
send()
recv()

// 4. 断开
close()
```

### `int socket(int domain, int type, int protocol)`

#### domain: 
Name         Purpose                                    Man page  
AF_UNIX      Local communication                        unix(7)  

AF_LOCAL     Synonym for AF_UNIX  

AF_INET      IPv4 Internet protocols                    ip(7)  

AF_AX25      Amateur radio AX.25 protocol               ax25(4)  

AF_IPX       IPX - Novell protocols  

AF_APPLETALK AppleTalk                                  ddp(7)  

AF_X25       ITU-T X.25 / ISO-8208 protocol             x25(7)  

AF_INET6     IPv6 Internet protocols                    ipv6(7)  

AF_DECnet    DECet protocol sockets  

AF_KEY       Key  management protocol, originally de‐  
            veloped for usage with IPsec  

AF_NETLINK   Kernel user interface device               netlink(7) 

AF_PACKET    Low-level packet interface                 packet(7)  

AF_RDS       Reliable Datagram Sockets (RDS) protocol   rds(7)  
                                                        rds-rdma(7)  

AF_PPPOX     Generic PPP transport layer, for setting  
            up L2 tunnels (L2TP and PPPoE)  

AF_LLC       Logical  link  control  (IEEE 802.2 LLC)  
            protocol  

AF_IB        InfiniBand native addressing  

AF_MPLS      Multiprotocol Label Switching  

AF_CAN       Controller Area Network  automotive  bus protocol  

AF_TIPC      TIPC, "cluster domain sockets" protocol  

AF_BLUETOOTH Bluetooth low-level socket protocol  

AF_ALG       Interface to kernel crypto API  

AF_VSOCK     VSOCK   (originally  "VMWare  VSockets")   vsock(7)
            protocol for hypervisor-guest communication 

AF_KCM       KCM  (kernel connection multiplexer) in‐terface  

AF_XDP       XDP (express data path) interface  

#### type

 The socket has the indicated type, which specifies the communication semantics.  Currently defined types are:

SOCK_STREAM     Provides sequenced, reliable, two-way, connection-based byte streams.  An out-of-band data transmission mech‐anism may be supported. 

SOCK_DGRAM      Supports datagrams (connectionless, unreliable messages of a fixed maximum length).

SOCK_SEQPACKET  Provides a sequenced, reliable, two-way connection-based data transmission path for datagrams of fixed  maxi‐mum length; a consumer is required to read an entire packet with each input system call.

SOCK_RAW        Provides raw network protocol access.

SOCK_RDM        Provides a reliable datagram layer that does not guarantee ordering.

SOCK_PACKET     Obsolete and should not be used in new programs; see packet(7).





### `int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)`;
将fd 和 ip.port 关联

### `int listen(int sockfd, int backlog)`;
监听fd上面连接; 
backlog: 未连接和已连接的最大值, `cat /proc/sys/net/core/somaxconn`

### `int accept(int sockfd, struct sockaddr * addr, socklent_t *addrlen)`;
接受client 连接， 默认为阻塞;

addr: 传出参数， 记录连接成功后客户端的地址信息 ip, port

### `int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)`;
连接服务器；


### `ssize_t write(int fd, const void *buf, size_t count)`;

### `ssize_t read(int fd, void *buf, size_t count)`;





