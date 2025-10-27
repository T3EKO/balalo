#include "round_manager.h"
#include "run_manager.h"

RoundManager::RoundManager(std::shared_ptr<RunManager> runManager) : runManager{runManager} { }

std::shared_ptr<RunManager> RoundManager::getRunManager() {
    return runManager;
}

void RoundManager::init() {
    cardsInDeck = runManager->getDeck()->getCards();
    hand = {8};
    cardsDiscarded = {};

    gen = std::mt19937{19937};
}

double RoundManager::getRoundScore() {
    return roundScore;
}

Array<std::shared_ptr<PlayingCard>> RoundManager::getCardsInHand() {
    Array<std::shared_ptr<PlayingCard>> playingCards{};
    Array<std::shared_ptr<Card>> cards = hand.getAllCards();
    for(size_t i = 0;i < cards.size();i++) {
        playingCards.append(std::dynamic_pointer_cast<PlayingCard>(cards[i]));
    }
    return playingCards;
}

Array<size_t> RoundManager::getSelectedIndices() {
    return hand.getSelectedIndices();
}

void RoundManager::drawCard() {
    u_int32_t randomInt = gen();
    size_t cardIndex = randomInt % cardsInDeck.size();
    std::shared_ptr<PlayingCard> card = cardsInDeck.removeAt(cardIndex);
    hand.addCard(std::dynamic_pointer_cast<Card>(card));
}

void RoundManager::drawCards(size_t amount) {
    for(size_t i{0};i < amount;i++) {
        drawCard();
    }
}

void RoundManager::drawUp() {
    if(hand.getCurrentSize() < hand.getCapacity()) {
        drawCards(hand.getCapacity() - hand.getCurrentSize());
    }
}

void RoundManager::selectCard(size_t idx) {
    hand.selectCard(idx);
}

void RoundManager::selectCards(Array<size_t> idcs) {
    hand.selectCards(idcs);
}

void RoundManager::deselectCard(size_t idx) {
    hand.deselectCard(idx);
}

void RoundManager::deselectCards(Array<size_t> idcs) {
    hand.deselectCards(idcs);
}

void RoundManager::deselectAllCards() {
    hand.deselectAllCards();
}

bool RoundManager::moveSelectedCard(size_t newIdx) {
    Array<size_t> selectedIdcs = hand.getSelectedIndices();
    if(selectedIdcs.size() != 1) return false;
    hand.moveCard(selectedIdcs[0], newIdx);
    return true;
}

bool RoundManager::swapSelectedCards() {
    Array<size_t> selectedIdcs = hand.getSelectedIndices();
    if(selectedIdcs.size() != 2) return false;
    hand.swapCards(selectedIdcs[0], selectedIdcs[1]);
    return true;
}

void RoundManager::discardSelectedCards() {
    Array<std::shared_ptr<Card>> cards = hand.removeSelectedCards();
    for(size_t i = 0;i < cards.size();i++) {
        cardsDiscarded.append(std::dynamic_pointer_cast<PlayingCard>(cards[i]));
    }
}

void RoundManager::playSelectedCards() {
    Array<std::shared_ptr<Card>> cards = hand.removeSelectedCards();

    
}

void RoundManager::sortHandByRank() {
    hand.sortCards([](std::shared_ptr<Card> a, std::shared_ptr<Card> b) {
        return PlayingCard::rankOrderSortPredicate(std::dynamic_pointer_cast<PlayingCard>(a), std::dynamic_pointer_cast<PlayingCard>(b));
    });
}

void RoundManager::sortHandBySuit() {
    hand.sortCards([](std::shared_ptr<Card> a, std::shared_ptr<Card> b) {
        return PlayingCard::suitOrderSortPredicate(std::dynamic_pointer_cast<PlayingCard>(a), std::dynamic_pointer_cast<PlayingCard>(b));
    });
}
