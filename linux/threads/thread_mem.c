#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *p_num;

void *thread_1(void *args)
{
    int test_num = 1;

    printf("test_num: %dn", test_num);

    p_num = &test_num;

    sleep(2);

    printf("test_num: %dn", test_num);
}

void *thread_2(void *args)
{
    sleep(1);

    if (p_num != NULL) {
        *p_num = 2;
    }
}

int main(int argc, char *argv[])
{
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_1, NULL);
    pthread_create(&thread2, NULL, thread_2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return EXIT_SUCCESS;
}

