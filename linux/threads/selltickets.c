#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int tickets = 10;

void * selltickets(void *) {

    // int tickets = 10; 这里会让每个线程都有一份

    while (tickets > 0) {
        printf("machine-%ld sell %d ticket \n", pthread_self(), tickets);
        // sleep(1);
        usleep(10000 * 1000);
        tickets--;
    }
    return NULL;
}

int main() {

    pthread_t tid1, tid2, tid3;

    pthread_create(&tid1, NULL, selltickets, NULL);
    pthread_create(&tid2, NULL, selltickets, NULL);
    pthread_create(&tid3, NULL, selltickets, NULL);


    // 回收子线程
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    // 线程分离: 回收之后分离意义不大
    // pthread_detach(tid1);
    // pthread_detach(tid1);
    // pthread_detach(tid1);

    // 推出
    pthread_exit(NULL);


    return 0;
}
