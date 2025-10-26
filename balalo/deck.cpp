#include "deck.h"
#include <cstdint>

Deck::Deck() { }

Deck Deck::buildStandard() {
    Deck deck{};
    for(Suit isuit{0};isuit <= 3;isuit++) {
        deck.cards.append(std::make_shared<PlayingCard>(PlayingCard{isuit, Ranks::ACE, 11}));
        for(Rank irank{13};irank >= 11;irank--) {
            deck.cards.append(std::make_shared<PlayingCard>(PlayingCard{isuit, irank, 10}));
        }
        for(Rank irank{10};irank >= 2;irank--) {
            deck.cards.append(std::make_shared<PlayingCard>(PlayingCard{isuit, irank, (double)irank}));
        }
    }
    return deck;
}

Array<std::shared_ptr<PlayingCard>> Deck::getCards() {
    return cards;
}