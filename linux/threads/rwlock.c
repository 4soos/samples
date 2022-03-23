/*
    读写锁的类型 pthread_rwlock_t
    int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr);
    int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
    int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
    int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
    int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
    int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
    int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

    案例：8个线程操作同一个全局变量。
    3个线程不定时写这个全局变量，5个线程不定时的读这个全局变量
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

int num = 0;
pthread_mutex_t mtx;

void * write_num(void * arg) {
    while (true) {
        pthread_mutex_lock(&mtx);
        num++;
        printf("W :: tid: %ld , write num %d \n", pthread_self(), num);
        usleep(1000*1000);
        pthread_mutex_unlock(&mtx);
    }
}
void * read_num(void * arg) {
    while (true) {
        pthread_mutex_lock(&mtx);
        printf("R :: tid: %ld , read num %d \n", pthread_self(), num);
        usleep(100*1000);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main() {
    
    // 创建
    pthread_t wtids[3], rtids[5];
    pthread_mutex_init(&mtx, NULL);

    for (int i=0; i < 3; i++) {
        pthread_create(&wtids[i], NULL, write_num, NULL);
    }

    for (int i=0; i < 5; i++) {
        pthread_create(&rtids[i], NULL, read_num, NULL);
    }

    // 线程分离
    for (int i=0; i < 3; i++) {
        pthread_detach(wtids[i]);
    }

    for (int i=0; i < 5; i++) {
        pthread_detach(rtids[i]);
    }

    // 主线程推出保证子线程正常运行
    pthread_exit(NULL);
    pthread_mutex_destroy(&mtx);

    return 0;
}
