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

    drawUp();
}

double RoundManager::getRoundScore() {
    return roundScore;
}

size_t RoundManager::getHandCapacity() {
    return hand.getCapacity();
}

size_t RoundManager::getCurrentHandSize() {
    return hand.getCurrentSize();
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

bool RoundManager::drawUp() {
    if(hand.getCurrentSize() < hand.getCapacity()) {
        size_t deficit = hand.getCapacity() - hand.getCurrentSize();
        size_t cardsLeftInDeck = cardsInDeck.size();
        if(cardsLeftInDeck < deficit) {
            drawCards(cardsLeftInDeck);
            return false;
        }
        drawCards(deficit);
        return true;
    }
    return false;
}

void RoundManager::selectCard(size_t idx) {
    if(getSelectedIndices().size() >= maxSelection) return;
    hand.selectCard(idx);
}

void RoundManager::selectCards(Array<size_t> idcs) {
    for(size_t i = 0;i < idcs.size();i++) {
        if(getSelectedIndices().size() >= maxSelection) return;
        hand.selectCard(idcs[i]);
    }
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

void RoundManager::toggleCardSelected(size_t idx) {
    if(getSelectedIndices().size() >= maxSelection) {
        deselectCard(idx);
        return;
    }
    hand.toggleCardSelected(idx);
}

void RoundManager::moveCard(size_t cidx, size_t nidx) {
    hand.moveCard(cidx, nidx);
}

void RoundManager::discardSelectedCards() {
    Array<std::shared_ptr<Card>> cards = hand.removeSelectedCards();
    for(size_t i = 0;i < cards.size();i++) {
        cardsDiscarded.append(std::dynamic_pointer_cast<PlayingCard>(cards[i]));
    }

    drawUp();
}

void RoundManager::playSelectedCards() {
    Array<std::shared_ptr<Card>> cards = hand.removeSelectedCards();
    if(cards.size() == 0) return;
    Array<std::shared_ptr<PlayingCard>> playingCards{};
    for(size_t i = 0;i < cards.size();i++) {
        playingCards.append(std::dynamic_pointer_cast<PlayingCard>(cards[i]));
    }

    HandCheckResult handCheckResult = runManager->checkHand(playingCards);
    HandInfo highestPriorityHand = handCheckResult.getHighestPriorityHand();
    size_t bestMatch = highestPriorityHand.getBestMatch(handCheckResult.cards);
    Array<size_t> cardIdcs{};
    for(size_t i = 0;i < handCheckResult.cards.size();i++) {
        cardIdcs.append(i);
    }
    Array<size_t> scoringIdcs = cardIdcs.filterByMask(bestMatch);

    std::shared_ptr<HandInstance> hand = highestPriorityHand.hand;

    double chips = hand->getChips();
    double mult = hand->getMult();

    for(size_t i = 0;i < scoringIdcs.size();i++) {
        std::shared_ptr<PlayingCard> card = handCheckResult.cards[scoringIdcs[i]];
        double value = card->getValue();
        chips += value;
    }

    double score = chips * mult;
    roundScore += score;

    drawUp();
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
