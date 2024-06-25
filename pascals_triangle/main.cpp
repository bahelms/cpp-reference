#include <algorithm>
#include <cassert>
#include <format>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ostream>
#include <ranges>
#include <vector>

/*
  // C++11 uniform initialization syntax
  std::vector<int> data{1};

  // C++17 class template argument deduction CTAD - no type param needed
  std::vector data1{1};
*/

std::vector<int> get_next_row(const std::vector<int> &last_row) {
    std::vector next_row{1};
    if (last_row.empty()) {
        return next_row;
    }

    for (size_t i = 0; i + 1 < last_row.size(); i++) {
        next_row.emplace_back(last_row[i] + last_row[i + 1]);
    }
    next_row.emplace_back(1);
    return next_row;
}

auto generate_triangle(int rows) {
    std::vector<std::vector<int>> triangle{{1}};

    for (int row_count = 1; row_count < rows; ++row_count) {
        triangle.push_back(get_next_row(triangle.back())); // perfect forwarding
    }
    return triangle;
}

template <typename T>
std::ostream &operator<<(std::ostream &s,
                         const std::vector<std::vector<T>> &triangle) {
    for (const auto &row : triangle) {
        // C++20 -std=c++2a
        std::ranges::copy(row, std::ostream_iterator<T>(s, " "));
        s << '\n';
    }
    return s;
}

void show_vectors(std::ostream &s, const std::vector<std::vector<int>> &v) {
    size_t final_row_size = v.back().size();
    std::string spaces(final_row_size * 3, ' ');

    for (const auto &row : v) {
        s << spaces;
        if (spaces.size() > 3) {
            spaces.resize(spaces.size() - 3);
        }
        for (const auto &data : row) {
            // C++20
            s << std::format("{: ^{}}", data, 6);
        }
        s << '\n';
    }
}

void show_odds(std::ostream &s, const std::vector<std::vector<int>> &v) {
    std::string spaces(v.back().size(), ' ');
    for (const auto &row : v) {
        s << spaces;
        if (spaces.size()) {
            spaces.resize(spaces.size() - 1);
        }
        auto odds = row | std::views::transform(
                              [](int x) { return x % 2 ? '*' : ' '; });
        for (const auto &data : odds) {
            s << data << ' ';
        }
        s << '\n';
    }
}

bool is_palindrome(const std::vector<int> &v) {
    auto forward = std::views::take(v, v.size() / 2);
    auto backward = v | std::views::reverse | std::views::take(v.size() / 2);
    return std::ranges::equal(forward, backward);
}

void assert_properties(const std::vector<std::vector<int>> &triangle) {
    size_t row_number = 1;
    int expected_total = 1;

    for (const auto &row : triangle) {
        assert(row.front() == 1);
        assert(row.back() == 1);
        assert(row.size() == row_number++);
        assert(std::accumulate(row.begin(), row.end(), 0) == expected_total);
        expected_total *= 2;

        auto is_positive = [](auto x) { return x > 0; };
        assert(std::ranges::all_of(row, is_positive)); // C++20
        assert(is_palindrome(row));
    }
}

int main() {
    auto triangle = generate_triangle(16);
    assert_properties(triangle);
    show_vectors(std::cout, triangle);
    show_odds(std::cout, triangle);
}
