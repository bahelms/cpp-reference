#include "playing_cards.h"
#include <iostream>
using namespace cards;

int main() {
  Card card{FaceValue{2}, Suit::Clubs};
  Card imp;
  if (card > imp) {
    std::cout << "Card is higher than imp: " << (card < imp) << std::endl;
  }
  if (imp == card) {
    std::cout << "Card is higher than imp: " << (card == imp) << std::endl;
  }
  if (imp > card) {
    std::cout << "Card is less than imp: " << (card == imp) << std::endl;
  }
}
