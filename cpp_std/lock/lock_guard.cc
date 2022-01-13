#include <functional>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <vector>

std::mutex mtx;
std::once_flag flag;

void print_block(int n, char c) {
    std::unique_lock<std::mutex> lck(mtx);
    for (int i=0; i < n; ++i) std::cout << c;

    std::cout << "\n";
}

void run_once(int &n) {
    std::call_once( flag, [&n]{ n = n + 1; } );
}

int main(int argc, char *argv[]) {
    std::vector<std::thread> ver;
    int num = 0;

    for (auto i=0; i < 10; ++i) {
        ver.emplace_back(print_block, 50, '*');
        ver.emplace_back(run_once, std::ref(num));
    }

    for (auto &t : ver) {
        
    }



}
