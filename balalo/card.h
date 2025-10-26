#pragma once

class Card {
private:
    bool selected = false;
    bool flipped = false;

public:
    Card();

    virtual bool isSelected();
    virtual bool isFlipped();

    virtual void setSelected(bool v);
    virtual void toggleSelected();

    virtual void setFlipped(bool v);
    virtual void toggleFlipped();
};