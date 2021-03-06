#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>

struct Node {
    int num;
    struct Node * next;
};

struct Node * head = NULL;

pthread_mutex_t mtx;
pthread_cond_t condtion;

sem_t psem;
sem_t csem;

void * producer(void * arg) {

    while (true) {
        sem_wait(&psem);

        pthread_mutex_lock(&mtx);
        struct Node * new_node  = (struct Node *) malloc(sizeof(struct Node));
        new_node->next = head;
        head = new_node;
        new_node->num = rand() % 1000;
        printf("PRODUCER:: add node, num: %d l tid-%ld \n", new_node->num, pthread_self());
        pthread_mutex_unlock(&mtx);

        sem_post(&csem); // 通知消费者

        usleep(100);
    }

    return NULL;
}


void * customer(void * arg) {

    while (true) {
        sem_wait(&csem);

        pthread_mutex_lock(&mtx);
        struct Node * tmp = head;
        head = head->next;
        printf("CUSTOMER:: delete node , num: %d ; tid-%ld \n", tmp->num, pthread_self());
        free(tmp);
        pthread_mutex_unlock(&mtx);

        sem_post(&psem);
    }
    
    return NULL;
}


int main() {

    pthread_t ptid[5], ctids[5];

    pthread_mutex_init(&mtx, NULL);

    sem_init(&psem, 0, 8);
    sem_init(&csem, 0, 0);


    for (int i = 0; i < 5; i++) {
        pthread_create(&ptid[i], NULL, producer, NULL);
        pthread_create(&ctids[i], NULL, customer, NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_detach(ptid[i]);
        pthread_detach(ctids[i]);
    }

    while (true) {
        sleep(4);
    }

    pthread_mutex_destroy(&mtx);
    pthread_exit(NULL);

    

    return 0;
}