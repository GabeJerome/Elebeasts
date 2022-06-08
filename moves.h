#pragma once

using namespace std;

enum element
{
    normal, fire, water, grass, electric, ice, fighting, poison,
    ground, flying, psychic, bug, rock, ghost, dragon, dark, steel, fairy
};

#ifndef __MOVES_H__
#define __MOVES_H__

class Move
{
public:
    Move( );
    Move( string moveName, int moveType, int moveElement, int moveAccuracy, int movePower );
    ~Move( );

    string name;
    int type;
    int element;
    int accuracy;
    int power;
};

#endif



inline Move::Move( )
{
    type = 0;
    element = 0;
    accuracy = 0;
    power = 0;
}


inline Move::Move( string moveName, int moveType, int moveElement, int moveAccuracy,
    int movePower )
{
    name = moveName;
    type = moveType;
    element = moveElement;
    accuracy = moveAccuracy;
    power = movePower;
}

inline Move::~Move( )
{

}

/*normal moves*/
const Move swipe( "swipe", 1, normal, 100, 20 );

const Move cinder( "cinder", 0, fire, 100, 30 );

const Move dowse( "dowse", 1, water, 100, 30 );

const Move thorn( "thorn", 1, grass, 100, 30 );