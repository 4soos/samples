#include <stdio.h>

// Get the 'postion' bit value
#define GET_BIT(X, POSTION)                    ((X & (1 << POSTION)) >> POSTION)

// Get value from N to M
#define BIT_M_TO_N(x, m, n)  ((unsigned int)(x << (31-(n))) >> ((31 - (n)) + (m)))


int main () {
    int t = 0x68;
    printf("p:    %d", GET_BIT(t,2));

    printf("n-m: %d", BIT_M_TO_N(t, 3,2));

    return 0;
}

