#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <fcntl.h>
#include <net/bpf.h>
#include <net/ethertypes.h>
#include <net_if_ether.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>


/**
* 如何在QNX中直接基于数据链路层发送裸数据
*/

int main(int argc, char *argv[]) {

    char bpfname[16] = {"/dev/bpf\0"};
    int fd = open(bpfname, O_RDWR);

    if (fd < 0) {
        for (int i=0; i < 128; i++) {
            snprintf(bpfname, sizeof(bpfname), "/dev/bpf%d", i);
            fd = open(bpfname, O_RDWR);
            
            if (fd != -1)
                break;
        }
        if (fd < 0) {
            perror("cloud not open any /dev/bpf device.");
            return -1;
        }
    }

    struct ifreq req;
    snprintf(req.ifr_name, sizeof(req.ifr_name), "%s", argv[1]);
    /**
    * 选定发送数据时需要使用的设备。类似于eth0这类的接口名称。
    * 这里我们通过命令行参数argv[1]传入。
    **/
    if (ioctl(fd, BIOCSETIF, &req) > 0) {
        perror("Cloud not bing to BPF");
        return -1;
    }

    int hdr_complete = 1;
    /**
    * 禁用自动添加的以太网报头。
    * 也就是说，目标MAC地址，自身MAC地址，以太网类型都由我们自己来写入。
    **/
    if (ioctl(fd, BIOCSHDRCMPLT, &hdr_complete) == -1) {
        perror("Could get disable HDRCMPLT \n");
        return -1;
    }

    int pdu_size = 1500;
    char pdu[pdu_size];

    /**
    * 前12个Bytes分别是目标MAC地址和源MAC地址。这里为了省事就不特意设定了。
    **/
    for (int i=0; i < pdu_size; i++) {
        pdu[i] = i % 255;
    }

    /**
    * 写入以太网类型。
    */
    #define ETH_TYPE 0x1234
    pdu[12] = (char)(ETH_TYPE >> 8);
    pdu[13] = (char)(ETH_TYPE & 0x00FF);

    /**
    * 发送做好的数据包。
    */
    if (write(fd, pdu, pdu_size) < 0)
        perror("Failed to send data");

    close(fd);

    return 0;
}

