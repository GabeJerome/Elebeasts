#pragma once

using namespace std;

enum moveElement { normal, fire, water, grass };

class Move
{
public:
    Move(int moveType, int moveElement, int moveAccuracy, int movePower);
    ~Move();

    int type;
    int element;
    int accuracy;
    int power;
};


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