#include <cassert>
#include <concepts>
#include <format>
#include <functional>
#include <iostream>
#include <limits>
#include <optional>
#include <random>

constexpr bool is_prime(int n) {
    if (n == 2 || n == 3) {
        return true;
    }
    if (n <= 1 || n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for (int i = 5; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

unsigned random_prime_number() {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist(1, 99999);
    int n{};
    while (!is_prime(n)) {
        n = dist(engine);
    }
    return n;
}

std::optional<int> read_number(std::istream &in) {
    int result{};
    if (in >> result) {
        return result;
    }
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return {};
}

void guess_number(int number, auto messages) {
    std::optional<int> guess; // C++17

    std::cout << "Guess the number.\n";
    while ((guess = read_number(std::cin))) {
        if (guess.value() == number) {
            std::cout << "Well done.\n" << std::endl;
            return;
        }
        std::cout << std::format("{:0>5} is wrong. Try again\n", guess.value());
        for (auto message : messages) {
            auto clue = message(guess.value());
            if (clue.length()) {
                std::cout << clue;
                break;
            }
        }
    }
    std::cout << std::format("The number was {:0>5}\n", number);
}

constexpr std::string validate_guess(int number, int guess) {
    auto ns = std::format("{:0>5}", number);
    auto gs = std::format("{:0>5}", guess);
    std::string matches(5, '.');

    // check positional matches
    for (size_t i = 0, stop = gs.length(); i < stop; i++) {
        char guess_char = gs[i];
        if (i < ns.length() && guess_char == ns[i]) {
            matches[i] = '*';
            ns[i] = '*';
        }
    }

    // check misplaced matches
    for (size_t i = 0, stop = gs.length(); i < stop; i++) {
        char guess_char = gs[i];
        if (i < ns.length() && matches[i] != '*') {
            // C++17 if(init; condition)
            if (size_t idx = ns.find(guess_char, 0); idx != std::string::npos) {
                matches[i] = '^';
                ns[idx] = '^';
            }
        }
    }
    return matches;
}

void check_properties() {
    static_assert(is_prime(2));
    static_assert(!is_prime(4));
    assert(validate_guess(12347, 23471) == "^^^^^");
    assert(validate_guess(65479, 50478) == "^.**.");
}

int main() {
    check_properties();
    auto check_prime = [](int guess) {
        return std::string(is_prime(guess) ? "" : "Not prime\n");
    };
    auto check_length = [](int guess) {
        return std::string(guess <= 99999 ? "" : "Too long\n");
    };

    const int number = random_prime_number();
    auto validation = [number](int guess) {
        return std::format("{}\n", validate_guess(number, guess));
    };

    // copying lambdas to std::function means they can't be inlined any more
    std::vector<std::function<std::string(int)>> messages{
        check_length, check_prime, validation};

    guess_number(number, messages);
}
