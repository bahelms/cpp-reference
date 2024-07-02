#pragma once

#include <array>
#include <iostream>
#include <stdexcept>

namespace cards {
enum class Suit { Hearts, Diamonds, Clubs, Spades };

class FaceValue {
public:
  // explicit prevents implicit casting of ints
  explicit FaceValue(int value) : value_(value) {
    if (value_ < 1 || value_ > 13) {
      throw std::invalid_argument("Face value invalid");
    }
  }

  int value() const { return value_; }

  auto operator<=>(const FaceValue &) const = default;

private:
  int value_;
};

class Card {
public:
  Card() = default;
  Card(FaceValue value, Suit suit) : value_(value), suit_(suit) {}

  FaceValue value() const { return value_; }
  Suit suit() const { return suit_; }

  // C++20
  auto operator<=>(const Card &) const = default;

private:
  FaceValue value_{1};
  Suit suit_{};
};

std::array<Card, 52> create_deck();

Suit &operator++(Suit &suit);
std::ostream &operator<<(std::ostream &os, const Card &card);

std::string to_string(const Suit &suit);
std::string to_string(const FaceValue &value);
} // namespace cards
