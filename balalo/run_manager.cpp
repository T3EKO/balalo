#include "run_manager.h"

#include "game_manager.h"

RunManager::RunManager(std::shared_ptr<GameManager> gameManager) : gameManager{gameManager} { }

std::shared_ptr<GameManager> RunManager::getGameManager() {
    return gameManager;
}

std::shared_ptr<Deck> RunManager::getDeck() {
    return deck;
}

std::shared_ptr<HandInstance> RunManager::getHand(size_t id) {
    return hands[id];
}

void RunManager::init() {
    hands = Array<std::shared_ptr<HandInstance>>{};
    Array<std::shared_ptr<HandType>> handTypes = gameManager->getAllHandTypes();
    for(size_t i = 0;i < handTypes.size();i++) {
        hands.append(std::make_shared<HandInstance>(HandInstance{handTypes[i]}));
    }

    deck = std::make_shared<Deck>(Deck::buildStandard());
}