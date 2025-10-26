#pragma once

#include <map>
#include "hand_type.h"
#include "hand_instance.h"
#include "round_manager.h"

class GameManager;

class RunManager {
private:
    std::shared_ptr<GameManager> gameManager;

    std::shared_ptr<Deck> deck;

    Array<std::shared_ptr<HandInstance>> hands;
public:
    RunManager(std::shared_ptr<GameManager> gameManager);

    std::shared_ptr<GameManager> getGameManager();

    std::shared_ptr<Deck> getDeck();

    std::shared_ptr<HandInstance> getHand(size_t id);

    void init();
};