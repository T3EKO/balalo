#include "run_manager.h"

#include "game_manager.h"

HandInfo::HandInfo(std::shared_ptr<HandInstance> hand, Array<size_t> matches) : hand{hand}, matches{matches} { }

size_t HandInfo::getBestMatch(Array<std::shared_ptr<PlayingCard>> cards) {
    if(matches.size() == 0) return 0;
    size_t bestScoringIndex = 0;
    size_t bestScore = 0;
    for(size_t i = 0;i < matches.size();i++) {
        Array<std::shared_ptr<PlayingCard>> matchCards = cards.filterByMask(matches[i]);
        size_t matchScore = 0;
        for(size_t j = 0;j < matchCards.size();j++) {
            matchScore += matchCards[j]->getScoringPriority();
        }
        if(matchScore > bestScore) {
            bestScoringIndex = i;
            bestScore = matchScore;
        }
    }
    return matches[bestScoringIndex];
}

HandCheckResult::HandCheckResult(Array<std::shared_ptr<PlayingCard>> cards) : cards{cards} { }

void HandCheckResult::checkHandInstance(std::shared_ptr<HandInstance> handInstance) {
    HandInfo handInfo{handInstance, handInstance->getAllMatches(cards)};
    if(handInfo.matches.size() == 0) return;
    hands.append(handInfo);
}

HandInfo HandCheckResult::getHighestPriorityHand() {
    size_t highestPriorityIndex = 0;
    for(size_t i = 1;i < hands.size();i++) {
        if(hands[i].hand->getPriority() > hands[highestPriorityIndex].hand->getPriority()) {
            highestPriorityIndex = i;
        }
    }
    return hands[highestPriorityIndex];
}

RunManager::RunManager(std::shared_ptr<GameManager> gameManager) : gameManager{gameManager} { }

std::shared_ptr<GameManager> RunManager::getGameManager() {
    return gameManager;
}

std::shared_ptr<Deck> RunManager::getDeck() {
    return deck;
}

HandCheckResult RunManager::checkHand(Array<std::shared_ptr<PlayingCard>> cards) {
    HandCheckResult res{cards};
    for(size_t i = 0;i < handInstances.size();i++) {
        res.checkHandInstance(handInstances[i]);
    }
    return res;
}

void RunManager::init() {
    handInstances = Array<std::shared_ptr<HandInstance>>{};
    Array<std::shared_ptr<HandType>> handTypes = gameManager->getAllHandTypes();
    for(size_t i = 0;i < handTypes.size();i++) {
        handInstances.append(std::make_shared<HandInstance>(HandInstance{handTypes[i]}));
    }

    deck = std::make_shared<Deck>(Deck::buildStandard());
}