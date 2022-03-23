/*
    互斥量的类型 pthread_mutex_t
    int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
        - 初始化互斥量
        - 参数 ：
            - mutex ： 需要初始化的互斥量变量
            - attr ： 互斥量相关的属性，NULL
        - restrict : C语言的修饰符，被修饰的指针，不能由另外的一个指针进行操作。
            pthread_mutex_t *restrict mutex = xxx;
            pthread_mutex_t * mutex1 = mutex;

    int pthread_mutex_destroy(pthread_mutex_t *mutex);
        - 释放互斥量的资源

    int pthread_mutex_lock(pthread_mutex_t *mutex);
        - 加锁，阻塞的，如果有一个线程加锁了，那么其他的线程只能阻塞等待

    int pthread_mutex_trylock(pthread_mutex_t *mutex);
        - 尝试加锁，如果加锁失败，不会阻塞，会直接返回。

    int pthread_mutex_unlock(pthread_mutex_t *mutex);
        - 解锁
*/

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
int tickets = 100;

pthread_mutex_t mutex;

void * selltickets(void *) {

    

    while (true) {
        pthread_mutex_lock(&mutex);
        if (tickets > 0) {
            printf("machine-%ld sell %d ticket \n", pthread_self(), tickets);
        // sleep(1);
            usleep(3000);
            tickets--;
        } else {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);
    }
    

    return NULL;
}

int main() {

    pthread_mutex_init(&mutex, NULL);

    pthread_t tid1, tid2, tid3;

    pthread_create(&tid1, NULL, selltickets, NULL);
    pthread_create(&tid2, NULL, selltickets, NULL);
    pthread_create(&tid3, NULL, selltickets, NULL);


    // 回收子线程
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    // 推出
    pthread_exit(NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}