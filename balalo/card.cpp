#include "card.h"

Card::Card() { }

bool Card::isSelected() {
    return selected;
}

bool Card::isFlipped() {
    return flipped;
}

void Card::setSelected(bool v) {
    selected = v;
}

void Card::toggleSelected() {
    selected = !selected;
}

void Card::setFlipped(bool v) {
    flipped = v;
}

void Card::toggleFlipped() {
    flipped = !flipped;
}