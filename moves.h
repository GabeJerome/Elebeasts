#pragma once
#include <string>

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
const Move swipe( "swipe", 1, normal, 100, 20 );    //0

const Move kick( "kick", 1, normal, 90, 30 );       //1

const Move cinder( "cinder", 0, fire, 100, 30 );    //2

const Move dowse( "dowse", 0, water, 100, 30 );     //3

const Move thorn( "thorn", 1, grass, 100, 30 );     //4


const Move allMoves[5] = { swipe, kick, cinder, dowse, thorn };