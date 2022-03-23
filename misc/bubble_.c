#include <stdio.h>

int xfun(int *a, int n){
    int x=*a;
    for(int *pa=a+1; pa<a+n; pa++) {
        printf(" *pa %d, pa %d , a %d \n", *pa, &pa, &a);
        if(*pa>x) x=*pa;
    }

    return x;
}

int main() {
    int x[8]={23,16,18,15,16,0, 19, 1};
    printf(" \n %d  \n",xfun(x,8) );

    return 0;
}
