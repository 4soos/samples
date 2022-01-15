#include <cstdint>
#include <iostream>
#include <cstring>
#include <array>

using namespace std;

struct test {
    int16_t len;
    uint32_t data;
    int *dynamic_arr;
};

int main(int argc, char * argv[]) {
    test t { 
        .len = 0,
        .data = 1111,
        .dynamic_arr = new int[10],
    };

    cout <<" " << t.len << endl;

    return 0;
}
