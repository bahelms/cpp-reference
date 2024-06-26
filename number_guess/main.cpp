#include <concepts>
#include <format>
#include <functional>
#include <iostream>
#include <limits>
#include <optional>

unsigned some_const_number() { return 42; }

std::optional<int> read_number(std::istream &in) {
    int result{};
    if (in >> result) {
        return result;
    }
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return {};
}

void guess_number(int number, std::invocable<int, int> auto message) {
    std::optional<int> guess; // C++17

    std::cout << "Guess the number.\n>";
    while ((guess = read_number(std::cin))) {
        if (guess.value() == number) {
            std::cout << "Well done.\n" << std::endl;
            return;
        }
        std::cout << message(number, guess.value());
        std::cout << '>';
    }
    std::cout << std::format("The number was {}\n", number);
}

int main() {
    auto message = [](int number, int guess) {
        return std::format("Your guess was too {}\n",
                           guess < number ? "small" : "big");
    };
    guess_number(some_const_number(), message);
}
