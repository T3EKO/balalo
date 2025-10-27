#pragma once

#include <map>
#include "hand_type.h"
#include "hand_instance.h"
#include "round_manager.h"

class GameManager;

struct HandInfo {
    std::shared_ptr<HandInstance> hand;
    Array<size_t> matches;

    HandInfo(std::shared_ptr<HandInstance> hand, Array<size_t> matches); 
};

struct HandCheckResult {
    Array<HandInfo> hands;
    Array<std::shared_ptr<PlayingCard>> cards;

    HandCheckResult(Array<std::shared_ptr<PlayingCard>> cards);

    void checkHandInstance(std::shared_ptr<HandInstance> handInstance);

    HandInfo getHighestPriorityHand();
};

class RunManager {
private:
    std::shared_ptr<GameManager> gameManager;

    std::shared_ptr<Deck> deck;

    Array<std::shared_ptr<HandInstance>> handInstances;

public:
    RunManager(std::shared_ptr<GameManager> gameManager);

    std::shared_ptr<GameManager> getGameManager();

    std::shared_ptr<Deck> getDeck();

    HandCheckResult checkHand(Array<std::shared_ptr<PlayingCard>> cards);



    void init();
};