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

void guess_number(int number) {
    std::optional<int> guess;

    std::cout << "Guess the number.\n>";
    while ((guess = read_number(std::cin))) {
        if (guess.value() == number) {
            std::cout << "Well done.\n" << std::endl;
            return;
        }
        std::cout << guess.value() << " is wrong. Try again\n>";
    }
    std::cout << "The number was " << number << std::endl;
}

int main() { guess_number(some_const_number()); }
