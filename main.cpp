#include "balalo.h"

using namespace std;
// using namespace raylib;

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

// void printScoringProcess(RoundManager& roundManager, ScoringResult res) {
//     Array<std::string> handNames{ "High Card", "Pair", "Two Pair", "Three of a Kind", "Straight", "Flush", "Full House", "Four of a Kind", "Straight Flush", "Five of a Kind", "Flush House", "Flush Five" };

//     cout << "\nCards played:\n";
//     printCardArray(res.cards);
//     cout << "Scoring cards: " << res.scoringCards.stringify([](size_t v) -> string {
//         return to_string(v);
//     }) << "\n";
//     cout << "\nHand: " << handNames[res.scoredHandId] << "\n";
//     cout << "\nBase score: " << res.baseChips << " Chips x " << res.baseMult << " Mult\n";

//     cout << "Card Scores:\n";
//     for(size_t i = 0;i < res.cardScores.size();i++) {
//         size_t cardIdx = res.cardScores[i].idx;
//         shared_ptr<PlayingCard> card = res.cards[cardIdx];
//         double chips = res.cardScores[i].chips;
//         double mult = res.cardScores[i].mult;
//         cout << "(" << i << ")\t" << card->getName() << ": +" << chips << " Chips, +" << mult << " Mult" << "\n";
//     }

//     cout << "\nFinal score: " << res.finalChips << " Chips x " << res.finalMult << " Mult\n";
//     cout << "\tScore: " << res.handScore << "\n";
//     cout << "Round Score: " << res.roundScore << "\n";

//     cout << "\nContinue?\n> ";
//     string userInput;
//     getline(cin, userInput);
// }

void promptPlay(std::shared_ptr<RoundManager> roundManager) {
    cin.ignore();
    cout << "\nWhich cards would you like to play?\n> ";
    string cards;
    getline(cin, cards);

    Array<size_t> cardIndices = parseIntArray(cards);

    // ScoringResult res = roundManager.playCards(cardIndices);

    // printScoringProcess(roundManager, res);
}

void promptSelect(std::shared_ptr<RoundManager> roundManager) {
    cin.ignore();
    cout << "\nWhich cards would you like to select?\n> ";
    string cards;
    getline(cin, cards);

    Array<size_t> cardIndices = parseIntArray(cards);

    roundManager->selectCards(cardIndices);
}

void promptDeselect(std::shared_ptr<RoundManager> roundManager) {
    cin.ignore();
    cout << "\nWhich cards would you like to deselect? (Entering nothing will deselect all cards)\n> ";
    string cards;
    getline(cin, cards);

    Array<size_t> cardIndices = parseIntArray(cards);

    if(cardIndices.size() == 0) {
        roundManager->deselectAllCards();
    }

    roundManager->deselectCards(cardIndices);
}

void promptMoveCard(std::shared_ptr<RoundManager> roundManager) {
    Array<size_t> selectedIdcs = roundManager->getSelectedIndices();
    if(selectedIdcs.size() != 1) {
        cout << "\nERROR: must have 1 card selected\n";
        return;
    }
    cin.ignore();
    cout << "\nWhere would you like to move?\n> ";
    string idxStr;
    getline(cin, idxStr);

    Array<size_t> idxArr = parseIntArray(idxStr);

    if(idxArr.size() == 0) {
        cout << "\nERROR: must enter a number\n";
        return;
    }

    size_t idx = idxArr[0];
    roundManager->moveSelectedCard(idx);
}

void promptAction(std::shared_ptr<RoundManager> roundManager) {
    cout << "\nCards in hand:\n";
    printCardArray(roundManager->getCardsInHand());
    cout << "\nWhat do you want to do?\n(s)\tSelect cards\n(u)\tDeselect cards\n(m)\tMove (1) selected card\n(w)\tSwap (2) selected cards\n(p)\tPlay\n(d)\tDiscard\n(r)\tSort by rank\n(i)\tSort by suit\n> ";
    string action;
    cin >> action;
    if(action == "s") {
        promptSelect(roundManager);
        return;
    }
    if(action == "u") {
        promptDeselect(roundManager);
        return;
    }
    if(action == "m") {
        promptMoveCard(roundManager);
        return;
    }
    if(action == "w") {
        bool swapSuccess = roundManager->swapSelectedCards();
        if(!swapSuccess) {
            cout << "ERROR: must have 2 cards selected\n";
        }
        return;
    }
    if(action == "d") {
        roundManager->discardSelectedCards();
        return;
    }
    if(action == "p") {
        promptPlay(roundManager);
        return;
    }
    if(action == "r") {
        roundManager->sortHandBySuit();
        roundManager->sortHandByRank();
        return;
    }
    if(action == "i") {
        roundManager->sortHandByRank();
        roundManager->sortHandBySuit();
    }
}

void playRound(std::shared_ptr<RunManager> runManager) {
    std::shared_ptr<RoundManager> roundManager{std::make_shared<RoundManager>(RoundManager{runManager})};

    roundManager->init();

    // printCardArray(runManager->getDeck()->getCards());

    while(true) {
        roundManager->drawUp();
        promptAction(roundManager);
    }
}

void playRun(std::shared_ptr<GameManager> gameManager) {
    std::shared_ptr<RunManager> runManager{std::make_shared<RunManager>(RunManager{gameManager})};

    runManager->init();

    playRound(runManager);
}

// void setupWindow() {
//     int width = 800;
//     int height = 450;
//     raylib::Color textColor = raylib::Color::Black();
//     Window window(width, height, "BALALO");

//     SetTargetFPS(165);

//     while(!window.ShouldClose()) {
//         while(window.Drawing()) {
//             window.ClearBackground(raylib::RAYWHITE);
//             textColor.DrawText("among us", 190, 200, 20);
//         }
//     }
// }

int main(int, char**) {
    std::shared_ptr<GameManager> gameManager{std::make_shared<GameManager>(GameManager{})};
    
    playRun(gameManager);

    return 0;
}
