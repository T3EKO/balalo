#pragma once

#include "../ulilities/array.h"
#include <iostream>
#include <string>
#include <memory>
#include <cstdint>
#include "card.h"

typedef uint32_t Suit;
typedef uint32_t Rank;

enum Suits : Suit {
    SPADES = 0,
    HEARTS = 1,
    CLUBS = 2,
    DIAMONDS = 3,
};

enum Ranks : Rank {
    NIL = 0,
    ACE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13
};

class PlayingCard : public Card {
private:
    Suit suit;
    Rank rank;
    double value;

public:
    PlayingCard(Suit suit, Rank rank, double value);

    bool hasSuit(Suit comp);

    Suit getSuit();
    size_t getSuitSortOrder();

    Rank getRank();
    size_t getRankSortOrder();

    double getValue();

    size_t getScoringPriority();

    static bool rankOrderSortPredicate(std::shared_ptr<PlayingCard> a, std::shared_ptr<PlayingCard> b);
    static bool suitOrderSortPredicate(std::shared_ptr<PlayingCard> a, std::shared_ptr<PlayingCard> b);

    std::string getName();

    static std::string stringify(PlayingCard card);
    static std::string stringifySharedPtr(std::shared_ptr<PlayingCard> card);
};