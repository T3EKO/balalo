#pragma once

#include <memory>
#include <random>
#include "deck.h"
#include "card_group.h"
#include "hand_instance.h"

class RunManager;

class RoundManager {
private:
    std::shared_ptr<RunManager> runManager;

    Array<std::shared_ptr<PlayingCard>> cardsInDeck;
    CardGroup hand;
    size_t maxSelection = 5;
    Array<std::shared_ptr<PlayingCard>> cardsDiscarded;

    std::mt19937 gen;

    double roundScore;

public:
    RoundManager(std::shared_ptr<RunManager> runManager);

    std::shared_ptr<RunManager> getRunManager();

    double getRoundScore();
    size_t getHandCapacity();
    size_t getCurrentHandSize();
    Array<std::shared_ptr<PlayingCard>> getCardsInHand();
    Array<size_t> getSelectedIndices();

    void init();

    void drawCard();
    void drawCards(size_t amount);
    bool drawUp();

    void selectCard(size_t idx);
    void selectCards(Array<size_t> idcs);
    void deselectCard(size_t idx);
    void deselectCards(Array<size_t> idcs);
    void deselectAllCards();

    void toggleCardSelected(size_t idx);

    // bool moveSelectedCard(size_t newIdx);
    // bool swapSelectedCards();

    void moveCard(size_t cidx, size_t nidx);

    void discardSelectedCards();
    void playSelectedCards();

    void sortHandByRank();
    void sortHandBySuit();

};