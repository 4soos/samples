#include <stdio.h>
#include <string.h>

void test(char* data) {

    if ( data == NULL) 
        strcpy(data, "test");
    
}


int main() {

    char* buf = NULL;
    test(buf);
    printf("%s", buf);

    return 0;
}
