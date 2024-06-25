#include <functional>
#include <iostream>

void add_nums(int, float);

auto main() -> int {
    std::cout << "Hello, world!\n";
    add_nums(1, 1.23);
}

void add_nums(int x, float y) {
    // std::plus<> is a class, {} inits it, () calls it
    std::cout << std::plus<int>{}(x, y) << '\n';
    std::cout << std::plus<>{}(x, y) << '\n';
}
