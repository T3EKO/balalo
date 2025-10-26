#pragma once

#include "hand_instance.h"
#include "run_manager.h"

class GameManager {
private:
    Array<std::shared_ptr<HandType>> handTypes;

public:
    GameManager();

    Array<std::shared_ptr<HandType>> getAllHandTypes();

    void init();
};