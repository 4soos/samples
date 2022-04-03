#include <stdio.h>

__attribute__((constructor)) void hello() {
    printf("Hello ");
}

__attribute__((destructor)) void world() {
    printf("World \n");
}


int main() {
}

