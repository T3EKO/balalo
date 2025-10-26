#pragma once
#include <string>
#include <memory>
#include "playing_card.h"
#include "../ulilities/array.h"

class Deck {
public:
    Array<std::shared_ptr<PlayingCard>> cards;

    Deck();

    static Deck buildStandard();

    Array<std::shared_ptr<PlayingCard>> getCards();
};