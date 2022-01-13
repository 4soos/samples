#include <threads.h>

#include<stdio.h>
#include<assert.h>
#include<threads.h>
 
int hello_word_thrd_fn(void *arg){
    printf("%lu, %s\n", thrd_current(), __func__);
}
 
int main(){
    thrd_t th;
    int status = thrd_create(&th, hello_word_thrd_fn, NULL);
    assert(("hello word thrd create error!!\n", status == thrd_success));
 
    thrd_join(th, NULL);
    printf("%lu, %s\n", thrd_current(), __func__);
}
 