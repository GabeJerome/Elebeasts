#pragma once

using namespace std;

enum moveElement { normal, fire, water, grass, electric, ice, fighting, poison,
    ground, flying, psychic, bug, rock, ghost, dragon, dark, steel, fairy };

class Move
{
public:
    Move();
    Move(int moveType, int moveElement, int moveAccuracy, int movePower);
    ~Move();

    int type;
    int element;
    int accuracy;
    int power;
};



inline Move::Move()
{
    type = 0;
    element = 0;
    accuracy = 0;
    power = 0;
}


inline Move::Move(int moveType, int moveElement, int moveAccuracy,
    int movePower)
{
    type = moveType;
    element = moveElement;
    accuracy = moveAccuracy;
    power = movePower;
}

inline Move::~Move()
{

}

const Move none(0, 0, 0, 0);

const Move swipe(1, normal, 100, 20);