#pragma once

#include "hand_type.h"

class HandInstance {
private:
    std::shared_ptr<HandType> type;

    size_t level = 1;
    double chips;
    double mult;

public:
    HandInstance(std::shared_ptr<HandType> type);

    std::string getName();

    Array<size_t> getAllMatches(Array<std::shared_ptr<PlayingCard>> cards);

    size_t getLevel();
    double getChips();
    double getMult();
};