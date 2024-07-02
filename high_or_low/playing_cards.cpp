#include "playing_cards.h"
#include <random>

namespace cards {

Deck create_deck() {
  Deck deck;
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

ExtendedDeck create_extended_deck() {
  ExtendedDeck deck{Joker(), Joker{}};
  Deck cards = create_deck();
  std::ranges::copy(cards, deck.begin() + 2);
  return deck;
}

template <typename T> void shuffle_deck(T &deck) {
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::ranges::shuffle(deck, gen);
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

std::ostream &operator<<(std::ostream &os,
                         const std::variant<Card, Joker> &card) {
  if (std::holds_alternative<Joker>(card)) {
    os << "JOKER";
  } else {
    os << std::get<Card>(card);
  }
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

bool is_guess_correct(char guess, const std::variant<Card, Joker> &current,
                      const std::variant<Card, Joker> &next) {
  if (std::holds_alternative<Joker>(current) ||
      std::holds_alternative<Joker>(next)) {
    return true;
  }
  Card current_card = std::get<Card>(current);
  Card next_card = std::get<Card>(next);
  return is_guess_correct(guess, current_card, next_card);
}

bool is_guess_correct(char guess, const Card &current, const Card &next) {
  return (guess == 'h' && next > current) || (guess == 'l' && next < current);
}

void higher_lower() {
  ExtendedDeck deck = create_extended_deck();
  shuffle_deck(deck);

  size_t index = 0;
  while (index + 1 < deck.size()) {
    std::cout << deck[index] << ": Next card higher (h) or lower (l)?\n>";

    char c;
    std::cin >> c;
    bool ok = is_guess_correct(c, deck[index], deck[index + 1]);
    if (!ok) {
      std::cout << "Next card was " << deck[index + 1] << '\n';
      break;
    }
    index++;
  }
  std::cout << "You got " << index << " correct\n";
}
} // namespace cards
