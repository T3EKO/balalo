#pragma once

#include "playing_card.h"
#include <memory>
#include <functional>
#include "../ulilities/array.h"

class HandType {
private:
    std::string name;
    std::function<bool(Array<std::shared_ptr<PlayingCard>>)> predicate;

    double baseChips;
    double baseMult;

public:
    HandType(std::string name, std::function<bool(Array<std::shared_ptr<PlayingCard>>)> predicate, double baseChips, double baseMult);

    std::string getName();

    Array<size_t> getAllMatches(Array<std::shared_ptr<PlayingCard>> cards);

    double getBaseChips();
    double getBaseMult();
};

Array<size_t> countRanks(Array<Rank> ranks);
Array<size_t> countRanks(Array<std::shared_ptr<PlayingCard>> cards);
bool isStraight(Array<Rank> ranks);
bool isUniqueSets(Array<Rank> ranks, Array<size_t> setSizes);

bool isStraight(Array<std::shared_ptr<PlayingCard>> cards, size_t runLength);
bool isFlush(Array<std::shared_ptr<PlayingCard>> cards, size_t size);
bool containsFlush(Array<std::shared_ptr<PlayingCard>> cards, size_t size);
bool isUniqueSets(Array<std::shared_ptr<PlayingCard>> cards, Array<size_t> setSizes);

Array<size_t> getAllValidHands(Array<std::shared_ptr<PlayingCard>> cards, std::function<bool(Array<std::shared_ptr<PlayingCard>> cards)> predicate);
