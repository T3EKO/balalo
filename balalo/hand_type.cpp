#include "hand_type.h"

HandType::HandType(std::string name, std::function<bool(Array<std::shared_ptr<PlayingCard>>)> predicate, double baseChips, double baseMult) : name{name}, predicate{predicate}, baseChips{baseChips}, baseMult{baseMult} { }

std::string HandType::getName() {
    return name;
}

double HandType::getBaseChips() {
    return baseChips;
}

double HandType::getBaseMult() {
    return baseMult;
}

Array<size_t> HandType::getAllMatches(Array<std::shared_ptr<PlayingCard>> cards) {
    return getAllValidHands(cards, predicate);
}

Array<size_t> countRanks(Array<Rank> ranks) {
    Array<size_t> rankAmounts{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for(size_t i = 0;i < ranks.size();i++) {
        rankAmounts[ranks[i]]++;
    }
    return rankAmounts;
}

Array<size_t> countRanks(Array<std::shared_ptr<PlayingCard>> cards) {
    Array<Rank> ranks{};
    for(size_t i = 0;i < cards.size();i++) {
        ranks.append(cards[i]->getRank());
    }
    return countRanks(ranks);
}

bool isStraight(Array<Rank> ranks) {
    ranks.sort([](Rank a, Rank b) -> bool {
        return a > b;
    });
    for(size_t i = 0;i < ranks.size() - 1;i++) {
        if(ranks[i] - ranks[i + 1] != 1) return false;
    }
    return true;
}

bool isUniqueSets(Array<Rank> ranks, Array<size_t> setSizes) {
    size_t totalRanksToCheck = 0;
    for(size_t i = 0;i < setSizes.size();i++) {
        totalRanksToCheck += setSizes[i];
    }
    if(ranks.size() != totalRanksToCheck) return false;
    if(totalRanksToCheck == 1) return true;
    Array<size_t> rankAmounts = countRanks(ranks);
    Array<size_t> setsInCards{};
    for(size_t i = 0;i < ranks.size() + 1;i++) {
        setsInCards.append(0);
    }
    for(size_t i = 0;i < rankAmounts.size();i++) {
        setsInCards[rankAmounts[i]]++;
    }
    Array<size_t> setsToCheck{};
    for(size_t i = 0;i < ranks.size() + 1;i++) {
        setsToCheck.append(0);
    }
    for(size_t i = 0;i < setSizes.size();i++) {
        setsToCheck[setSizes[i]]++;
    }
    for(size_t i = 1;i < setsInCards.size();i++) {
        if(setsInCards[i] != setsToCheck[i]) return false;
    }
    return true;
}

bool isStraight(Array<std::shared_ptr<PlayingCard>> cards, size_t runLength) {
    if(cards.size() != runLength) return false;
    Array<Rank> ranks{};
    for(size_t i = 0;i < cards.size();i++) {
        ranks.append(cards[i]->getRank());
    }
    bool hasStraight = isStraight(ranks);
    ranks.sort([](Rank a, Rank b) {
        return a < b;
    });
    if(ranks[0] == Ranks::ACE) {
        ranks[0] = 14;
        hasStraight = hasStraight || isStraight(ranks);
    }
    return hasStraight;
}

bool isFlush(Array<std::shared_ptr<PlayingCard>> cards, size_t size) {
    if(cards.size() != size) return false;
    for(size_t i = 0;i < cards.size() - 1;i++) {
        if(cards[i]->getSuit() != cards[i + 1]->getSuit()) return false;
    }
    return true;
}

bool containsFlush(Array<std::shared_ptr<PlayingCard>> cards, size_t size) {
    Array<size_t> suitAmounts{0, 0, 0, 0};
    for(size_t i = 0;i < cards.size();i++) {
        suitAmounts[cards[i]->getSuit()]++;
    }
    for(size_t i = 0;i < suitAmounts.size();i++) {
        if(suitAmounts[i] >= size) return true;
    }
    return false;
}

bool isUniqueSets(Array<std::shared_ptr<PlayingCard>> cards, Array<size_t> setSizes) {
    Array<Rank> ranks{};
    for(size_t i = 0;i < cards.size();i++) {
        ranks.append(cards[i]->getRank());
    }
    return isUniqueSets(ranks, setSizes);
}

Array<size_t> getAllValidHands(Array<std::shared_ptr<PlayingCard>> cards, std::function<bool(Array<std::shared_ptr<PlayingCard>> cards)> predicate) {
    Array<size_t> validHands;
    for(size_t handMask = 0;handMask < 1 << cards.size();handMask++) {
        if(predicate(cards.filterByMask(handMask))) {
            validHands.append(handMask);
        }
    }
    return validHands;
}
