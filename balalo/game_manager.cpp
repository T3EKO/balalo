#include "game_manager.h"

GameManager::GameManager() { }

Array<std::shared_ptr<HandType>> GameManager::getAllHandTypes() {
    return handTypes;
}

void GameManager::init() {
    handTypes = Array<std::shared_ptr<HandType>>{
        std::make_shared<HandType>(HandType{"High Card", [](auto cards) -> bool {
            return isUniqueSets(cards, { 1 });
        }, 5, 1}),
        std::make_shared<HandType>(HandType{"Pair", [](auto cards) -> bool {
            return isUniqueSets(cards, { 2 });
        }, 10, 2}),
        std::make_shared<HandType>(HandType{"Two Pair", [](auto cards) -> bool {
            return isUniqueSets(cards, { 2, 2 });
        }, 20, 2}),
        std::make_shared<HandType>(HandType{"Three of a Kind", [](auto cards) -> bool {
            return isUniqueSets(cards, { 3 });
        }, 30, 3}),
        std::make_shared<HandType>(HandType{"Straight", [](auto cards) -> bool {
            return isStraight(cards, 5);
        }, 30, 4}),
        std::make_shared<HandType>(HandType{"Flush", [](auto cards) -> bool {
            return isFlush(cards, 5);
        }, 35, 4}),
        std::make_shared<HandType>(HandType{"Full House", [](auto cards) -> bool {
            return isUniqueSets(cards, { 3, 2 });
        }, 40, 4}),
        std::make_shared<HandType>(HandType{"Four of a Kind", [](auto cards) -> bool {
            return isUniqueSets(cards, { 4 });
        }, 60, 7}),
        std::make_shared<HandType>(HandType{"Straight Flush", [](auto cards) -> bool {
            return isStraight(cards, 5) && containsFlush(cards, 5);
        }, 100, 8}),
        std::make_shared<HandType>(HandType{"Five of a Kind", [](auto cards) -> bool {
            return isUniqueSets(cards, { 5 });
        }, 120, 12}),
        std::make_shared<HandType>(HandType{"Flush House", [](auto cards) -> bool {
            return isUniqueSets(cards, { 3, 2 }) && containsFlush(cards, 5);
        }, 140, 14}),
        std::make_shared<HandType>(HandType{"Flush Five", [](auto cards) -> bool {
            return isUniqueSets(cards, { 5 }) && containsFlush(cards, 5);
        }, 160, 16})
    };
}