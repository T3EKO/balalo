#include "playing_card.h"

PlayingCard::PlayingCard(Suit suit, Rank rank, double value) : suit{suit}, rank{rank}, value{value} { }

bool PlayingCard::hasSuit(Suit comp) {
    return suit == comp;
}

u_int32_t PlayingCard::getSuit() {
    return suit;
}

size_t PlayingCard::getSuitSortOrder() {
    //                   W  M  C  D
    size_t sortOrders[]{ 0, 1, 2, 3 };
    return sortOrders[suit];
}

Rank PlayingCard::getRank() {
    return rank;
}

size_t PlayingCard::getRankSortOrder() {
    //                   nil  A  2   3   4   5  6  7  8  9  10 J  Q  K
    size_t sortOrders[]{ 255, 0, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    return sortOrders[rank];
}

double PlayingCard::getValue() {
    return value;
}

size_t PlayingCard::getScoringPriority() {
    //                          nil A  2  3  4  5  6  7  8  9  10  J   Q   K
    size_t scoringPriorities[]{ 1, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
    return scoringPriorities[rank];
}

bool PlayingCard::rankOrderSortPredicate(std::shared_ptr<PlayingCard> a, std::shared_ptr<PlayingCard> b) {
    return a->getRankSortOrder() < b->getRankSortOrder();
}

bool PlayingCard::suitOrderSortPredicate(std::shared_ptr<PlayingCard> a, std::shared_ptr<PlayingCard> b) {
    return a->getSuitSortOrder() < b->getSuitSortOrder();
}

std::string PlayingCard::getName() {
    std::string suitNames[]{ "Spades", "Hearts", "Clubs", "Diamonds" };
    std::string rankNames[]{ "", "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
    return rankNames[rank] + " of " + suitNames[suit];
}

std::string PlayingCard::stringify(PlayingCard card) {
    return card.getName();
}

std::string PlayingCard::stringifySharedPtr(std::shared_ptr<PlayingCard> card) {
    return card->getName();
}