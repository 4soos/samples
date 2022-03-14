#include <random>
#include <iostream>
#include <memory>
#include <functional>


void f(int n1, int n2, int n3, const int& n4, int n5) {
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << ' ' << '\n';
}


int g(int n1) {
    return n1;
}

struct Foo {
    void print_sum(int n1, int n2) {
        std::cout << n1 + n2 << '\n';
    }
    int data = 10;
};


int main() {
    using namespace std::placeholders;

    int n = 7;

    auto f1 = std::bind(f, _2, 42, _1, std::cref(n), n);

    n = 10;

    f1(1, 2, 1001);

    auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
    f2(10,11,12);



}

