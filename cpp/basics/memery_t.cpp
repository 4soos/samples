#include <iostream>
#include <cstdint>
#include <cstring>

int main() {
    char source[] = "once upon a midnight dreary", dest[4];


    std::memcpy(dest, source, sizeof dest);
    std::cout << "dest[4] = {";
    for (auto c: dest) std::cout << " ' " << c << " ', ";
    std::cout << "}'\n";

    double d = 0.1;

    std::int64_t n;
    std::memcpy(&n, &d, sizeof d);
    std::cout << std::hexfloat << d << " is " << std::hex << n 
        << "as an std::int64_t\n" << std::dec;
    
    struct S {
        int x[42];
        void print() const {
            std::cout << "{" << x << "}\n";
        }
    } s;

    alignas(S) char buf[sizeof(s)];
    S* ps = new (buf) S;
    std::memcpy(ps, &s, sizeof s);
    ps->print();

    return 0;
}