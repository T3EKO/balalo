cmake_minimum_required(VERSION 3.10.0)
project(Balalo VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(lib/FTXUI)

add_executable(Balalo balalo.h main.cpp
    ulilities/array.h ulilities/array.cpp
    balalo/card.h balalo/card.cpp
    balalo/playing_card.h balalo/playing_card.cpp
    balalo/card_group.h balalo/card_group.cpp
    balalo/deck.h balalo/deck.cpp
    balalo/hand_type.h balalo/hand_type.cpp
    balalo/hand_instance.h balalo/hand_instance.cpp
    balalo/round_manager.h balalo/round_manager.cpp
    balalo/run_manager.h balalo/run_manager.cpp
    balalo/game_manager.h balalo/game_manager.cpp
)

target_include_directories(Balalo PRIVATE $(CMAKE_CURRENT_BINARY_DIR)/lib/FTXUI)

target_link_libraries(Balalo
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
