#include <string>
#include <cstddef>
#include <concepts>
#include <tuple>


int main() {
    float x{};
    char y{};
    int z{};

    std::tuple<float&, char&&, int> tpl(x, std::move(y), z);
    const auto& [a, b, c] = tpl;


    return 0;
}

