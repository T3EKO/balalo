#include "balalo.h"

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
        roundManager->playSelectedCards();
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

int main(int, char**) {
    std::shared_ptr<GameManager> gameManager{std::make_shared<GameManager>(GameManager{})};
    
    playRun(gameManager);

    return 0;
}
