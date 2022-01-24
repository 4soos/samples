#include <iostream>

struct S {
    int n;
    char c[10];

} *p;

int main() {
    struct S a[3] = { {3, 'a'}, {4, 'b'}, {4, 'c'} };
    p = a;
    std::cout << (*p).n << std::endl;
    std::cout << p++ ->n << std::endl;
    
    return 0;
}
