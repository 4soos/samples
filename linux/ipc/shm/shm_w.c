#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <string.h>

int main() {

    int id = shmget(100, 4096, IPC_CREAT|0664);

    void * ptr = shmat(id, NULL, 0);

    char * str = "helloworld";
    memcpy(ptr, str, strlen(str) + 1);

    printf("input any key to continue ...");
    getchar();
    
    shmdt(ptr);

    shmctl(id, IPC_RMID, NULL);

    return 0;
}
