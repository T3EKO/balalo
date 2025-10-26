#include "hand_instance.h"

HandInstance::HandInstance(std::shared_ptr<HandType> type) : type{type}, level{1}, chips{type->getBaseChips()}, mult{type->getBaseMult()} { }

std::string HandInstance::getName() {
    return type->getName();
}

Array<size_t> HandInstance::getAllMatches(Array<std::shared_ptr<PlayingCard>> cards) {
    return type->getAllMatches(cards);
}

size_t HandInstance::getLevel() {
    return level;
}

double HandInstance::getChips() {
    return chips;
}

double HandInstance::getMult() {
    return mult;
}
