
#include <stdio.h>

int test(int a)
{
    return a * 2 - 10;
}

int main()
{
    for (int i=0; i <100; i++)
        printf("%d\n", test(i)+i);

    return 0;
}
