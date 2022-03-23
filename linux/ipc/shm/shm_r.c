#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <string.h>

int main() {

    int rid = shmget(100, 0, IPC_CREAT);
    printf("get rid %d \n", rid);

    void * ptr = shmat(rid, NULL, 0);
    printf("%s \n", (char *) ptr);

    printf("ttttt");
    getchar();

    shmdt(ptr);

    shmctl(rid, IPC_RMID, NULL);

    return 0;
}
