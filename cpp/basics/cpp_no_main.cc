#include <iostream>
#include <ostream>

int no_main() {
    std::cout << "output from no_main()" << std::endl;
}

void _start() {
    int ret = no_main();
}
