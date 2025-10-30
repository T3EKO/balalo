#include "balalo.h"

#include <chrono>
#include <cmath>

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

using namespace std;

void printArray(Array<u_int32_t> arr) {
    for(size_t index{0};index < arr.size();index++) {
        cout << arr[index];
        if(index < arr.size() - 1) cout << ", ";
    }
    cout << endl;
}

Array<size_t> parseIntArray(string str) {
    Array<size_t> values{};
    string currentValue{""};
    for(size_t i{0};i < str.length();i++) {
        char currentCharacter = str.at(i);
        if(currentCharacter >= '0' && currentCharacter <= '9') {
            currentValue += currentCharacter;
            continue;
        }
        if(currentCharacter == ',') {
            values.append(stoul(currentValue));
            currentValue = "";
        }
    }
    if(currentValue.length() > 0) {
        values.append(stoul(currentValue));
    }
    return values;
}

void printCardArray(Array<shared_ptr<PlayingCard>> cards) {
    string output{};
    for(size_t index{0};index < cards.size();index++) {
        bool cardSelected = cards[index]->isSelected();
        output += (cardSelected ? ">" : " ") + to_string(index) + (cardSelected ? "<| " : " | ") + cards[index]->getName();
        if(index < cards.size() - 1) output += "\n";
    }
    cout << output << endl;
}

void ftxuiMain() {
    using namespace ftxui;

    Array<string> suitNames = { "Spade", "Heart", "Diamo", "Clubs" };
    Array<Color> suitColors = { Color::White, Color::Red1, Color::Orange1, Color::SkyBlue1 };
    Array<string> rankNames = { " nil ", "A    ", "2    ", "3    ", "4    ", "5    ", "6    ", "7    ", "8    ", "9    ", "10   ", "J    ", "Q    ", "K    " };

    std::shared_ptr<GameManager> gameManager = std::make_shared<GameManager>();
    gameManager->init();
    std::shared_ptr<RunManager> runManager = std::make_shared<RunManager>(RunManager{gameManager});
    runManager->init();
    std::shared_ptr<RoundManager> roundManager = std::make_shared<RoundManager>(RoundManager{runManager});
    roundManager->init();
    
    size_t hoverIdx = 0;

    auto screen = ScreenInteractive::Fullscreen();
    auto renderer = Renderer([&] {
        Elements cardEls{};

        Array<std::shared_ptr<PlayingCard>> cardsInHand = roundManager->getCardsInHand();

        for(size_t i = 0;i < cardsInHand.size();i++) {
            Color col = suitColors[cardsInHand[i]->getSuit()];
            Element cardEl = vbox({
                text(rankNames[cardsInHand[i]->getRank()]),
                text(suitNames[cardsInHand[i]->getSuit()])
            }) | color(col);
            if(i == hoverIdx) {
                cardEl |= bold;
                cardEl |= borderHeavy;
            } else {
                cardEl |= border;
            }
            if(cardsInHand[i]->isSelected()) {
                cardEl = vbox({cardEl, text("")});
            } else {
                cardEl = vbox({text(""), cardEl});
            }
            cardEls.push_back(cardEl);
        }
    
        Element handEl = hbox({filler(), hbox(cardEls), filler()});

        Element document = hbox({
            separator(),
            vbox({
                text("left bar ") | flex,
                text(to_string(roundManager->getRoundScore()))
            }),
            separator(),
            vbox({
                hbox({
                    hbox({
                        text("jokers") | hcenter | flex_grow
                    }) | border | flex_grow,
                    hbox({
                        text("consumables") | hcenter | flex_grow
                    }) | border | flex_grow
                }),
                hbox({
                    vbox({
                        vbox({
                            text("center") | hcenter
                        }) | flex_grow,
                        handEl | hcenter,
                        text(to_string(roundManager->getCardsInHand().size()) + "/" + to_string(roundManager->getHandCapacity())) | hcenter
                    }) | flex_grow,
                    vbox({
                        text(" right bar ")
                    })
                }) | flex_grow
            }) | flex
        });
        return document;
    });
    auto eventCatcher = CatchEvent(renderer, [&](Event event) {
        if(event == Event::ArrowLeft) {
            if(hoverIdx == 0) {
                hoverIdx = roundManager->getCardsInHand().size() - 1;
            } else {
                hoverIdx--;
            }
            return true;
        }
        if(event == Event::ArrowRight) {
            hoverIdx = (hoverIdx + 1) % roundManager->getCardsInHand().size();
            return true;
        }
        if(event == Event::ArrowLeftCtrl) {
            hoverIdx = 0;
        }
        if(event == Event::ArrowRightCtrl) {
            hoverIdx = roundManager->getCardsInHand().size() - 1;
        }
        if(event == Event::Character('[')) {
            if(hoverIdx == 0) return false;
            roundManager->moveCard(hoverIdx, hoverIdx - 1);
            hoverIdx--;
            return true;
        }
        if(event == Event::Character(']')) {
            if(hoverIdx >= roundManager->getCardsInHand().size() - 1) return false;
            roundManager->moveCard(hoverIdx, hoverIdx + 1);
            hoverIdx++;
            return true;
        }
        if(event == Event::Character('r')) {
            roundManager->sortHandBySuit();
            roundManager->sortHandByRank();
            return true;
        }
        if(event == Event::Character('t')) {
            roundManager->sortHandByRank();
            roundManager->sortHandBySuit();
            return true;
        }
        if(event == Event::Character('x')) {
            roundManager->deselectAllCards();
            return true;
        }
        if(event == Event::Character(' ')) {
            roundManager->toggleCardSelected(hoverIdx);
            return true;
        }
        if(event == Event::Character('s')) {
            roundManager->discardSelectedCards();
            hoverIdx = clamp(hoverIdx, 0ul, roundManager->getCardsInHand().size() - 1);
            return true;
        }
        if(event == Event::Character('w')) {
            std::cout << "among us" << std::endl;
            roundManager->playSelectedCards();
            hoverIdx = clamp(hoverIdx, 0ul, roundManager->getCardsInHand().size() - 1);
            return true;
        }
        return false;
    });
    screen.Loop(eventCatcher);
}

int main(int, char**) {
    // std::shared_ptr<GameManager> gameManager{std::make_shared<GameManager>(GameManager{})};
    
    // playRun(gameManager);

    ftxuiMain();

    return 0;
}
