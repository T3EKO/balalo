#include "card_group.h"

CardGroup::CardGroup() : capacity{0} { }

CardGroup::CardGroup(size_t capacity) : capacity{capacity} { }

size_t CardGroup::getCapacity() {
    return capacity;
}

size_t CardGroup::getCurrentSize() {
    return cards.size();
}

std::shared_ptr<Card> CardGroup::getCard(size_t idx) {
    return cards[idx];
}

Array<std::shared_ptr<Card>> CardGroup::getCards(Array<size_t> idcs) {
    Array<std::shared_ptr<Card>> cards{};
    for(size_t i = 0;i < idcs.size();i++) {
        cards.append(getCard(idcs[i]));
    }
    return cards;
}

Array<std::shared_ptr<Card>> CardGroup::getAllCards() {
    return cards;
}

Array<size_t> CardGroup::getSelectedIndices() {
    Array<size_t> selectedIndices{};
    for(size_t i = 0;i < cards.size();i++) {
        if(!cards[i]->isSelected()) continue;
        selectedIndices.append(i);
    }
    return selectedIndices;
}

void CardGroup::addCard(std::shared_ptr<Card> card) {
    cards.append(card);
}

void CardGroup::moveCard(size_t cardIdx, size_t newIdx) {
    std::shared_ptr<Card> cardToMove = cards.removeAt(cardIdx);
    cards.insert(cardToMove, newIdx);
}

void CardGroup::swapCards(size_t idxA, size_t idxB) {
    std::shared_ptr<Card> cardA = cards[idxA];
    cards[idxA] = cards[idxB];
    cards[idxB] = cardA;
}

std::shared_ptr<Card> CardGroup::removeCard(size_t idx) {
    std::shared_ptr<Card> card = cards.removeAt(idx);
    card->setSelected(false);
    return card;
}

Array<std::shared_ptr<Card>> CardGroup::removeCards(Array<size_t> idcs) {
    Array<std::shared_ptr<Card>> cardsRemoved{};
    for(size_t i = 0;i < idcs.size();i++) {
        std::shared_ptr<Card> card = cards[idcs[i]];
        card->setSelected(false);
        cardsRemoved.append(card);
        cards[idcs[i]] = nullptr;
    }
    cards = cards.filter([](auto card, auto index, auto array) {
        return card != nullptr;
    });
    return cardsRemoved;
}

Array<std::shared_ptr<Card>> CardGroup::removeSelectedCards() {
    return removeCards(getSelectedIndices());
}

void CardGroup::sortCards(std::function<bool(std::shared_ptr<Card>, std::shared_ptr<Card>)> predicate) {
    cards.stable_sort(predicate);
}

void CardGroup::selectCard(size_t idx) {
    cards[idx]->setSelected(true);
}

void CardGroup::deselectCard(size_t idx) {
    cards[idx]->setSelected(false);
}

void CardGroup::toggleCardSelected(size_t idx) {
    cards[idx]->toggleSelected();
}

void CardGroup::selectCards(Array<size_t> idcs) {
    for(size_t i = 0;i < idcs.size();i++) {
        selectCard(idcs[i]);
    }
}

void CardGroup::deselectCards(Array<size_t> idcs) {
    for(size_t i = 0;i < idcs.size();i++) {
        deselectCard(idcs[i]);
    }
}
void CardGroup::toggleCardsSelected(Array<size_t> idcs) {
    for(size_t i = 0;i < idcs.size();i++) {
        toggleCardSelected(idcs[i]);
    }
}

void CardGroup::deselectAllCards() {
    for(size_t i = 0;i < cards.size();i++) {
        deselectCard(i);
    }
}