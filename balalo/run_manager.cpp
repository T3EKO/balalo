#include "run_manager.h"

#include "game_manager.h"

HandInfo::HandInfo(std::shared_ptr<HandInstance> hand, Array<size_t> matches) : hand{hand}, matches{matches} { }

HandCheckResult::HandCheckResult(Array<std::shared_ptr<PlayingCard>> cards) : cards{cards} { }

void HandCheckResult::checkHandInstance(std::shared_ptr<HandInstance> handInstance) {
    HandInfo handInfo{handInstance, handInstance->getAllMatches(cards)};
    hands.append(handInfo);
}

HandInfo HandCheckResult::getHighestPriorityHand() {
    size_t highestPriorityIndex = 0;
    for(size_t i = 1;i < hands.size();i++) {
        if(hands[i].hand->)
    }
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