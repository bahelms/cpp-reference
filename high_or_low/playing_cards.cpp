#include "playing_cards.h"
#include <type_traits>

namespace cards {

std::array<Card, 52> create_deck() {
  std::array<Card, 52> deck;
  int value = 1;
  Suit suit = Suit::Hearts;

  // calls lambda and assigns return value for each element in deck, C++20
  std::ranges::generate(deck, [&value, &suit]() {
    if (value > 13) {
      value = 1;
      ++suit;
    }
    return Card{FaceValue{value++}, suit};
  });
  return deck;
}

Suit &operator++(Suit &suit) {
  using IntType = std::underlying_type<Suit>::type;
  if (suit == Suit::Spades) {
    suit = Suit::Hearts;
  } else {
    suit = static_cast<Suit>(static_cast<IntType>(suit) + 1);
  }
  return suit;
}

std::ostream &operator<<(std::ostream &os, const Card &card) {
  os << to_string(card.value()) << " of " << to_string(card.suit());
  return os;
}

std::string to_string(const Suit &suit) {
  using namespace std::literals;

  switch (suit) {
  case Suit::Hearts:
    return "Hearts"s;
  case Suit::Clubs:
    return "Clubs"s;
  case Suit::Diamonds:
    return "Diamonds"s;
  case Suit::Spades:
    return "Spades"s;
  default:
    return "?"s;
  }
}

std::string to_string(const FaceValue &value) {
  using namespace std::literals;

  switch (value.value()) {
  case 1:
    return "Ace"s;
  case 11:
    return "Jack"s;
  case 12:
    return "Queen"s;
  case 13:
    return "King"s;
  default:
    return std::to_string(value.value());
  }
}
} // namespace cards
