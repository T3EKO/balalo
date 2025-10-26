#pragma once

#include <memory>
#include "../ulilities/array.h"
#include "card.h"

class CardGroup {
private:
    Array<std::shared_ptr<Card>> cards;

    size_t capacity;
public:
    CardGroup();
    CardGroup(size_t capacity);

    size_t getCapacity();
    size_t getCurrentSize();

    std::shared_ptr<Card> getCard(size_t idx);
    Array<std::shared_ptr<Card>> getCards(Array<size_t> idcs);
    Array<std::shared_ptr<Card>> getAllCards();
    Array<size_t> getSelectedIndices();

    void addCard(std::shared_ptr<Card> card);
    void moveCard(size_t cardIdx, size_t newIdx);
    void swapCards(size_t idxA, size_t idxB);
    std::shared_ptr<Card> removeCard(size_t idx);
    Array<std::shared_ptr<Card>> removeCards(Array<size_t> idcs);
    Array<std::shared_ptr<Card>> removeSelectedCards();

    void sortCards(std::function<bool(std::shared_ptr<Card>, std::shared_ptr<Card>)> predicate);

    void selectCard(size_t idx);
    void deselectCard(size_t idx);
    void toggleCardSelected(size_t idx);

    void selectCards(Array<size_t> idcs);
    void deselectCards(Array<size_t> idcs);
    void toggleCardsSelected(Array<size_t> idcs);

    void deselectAllCards();
};
