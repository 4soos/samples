#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_func(void *args)
{
    printf("tid: %u pid: %u thread id: %un", getpid(), syscall(224), pthread_self());

    while(1) {
        sleep(10);
    }
}

int main(int argc, char *argv[])
{
    pthread_t thread;
    int count = 0;

    while (pthread_create(&thread, NULL, thread_func, NULL) == 0) {
        sleep(1);
        count++;
    }

    perror("Create Error:");
    printf("Max Count:%dn", count);

    return EXIT_SUCCESS;
}
