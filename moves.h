#pragma once
#include <string>
#include <iomanip>

using namespace std;

enum element
{
    none = -1, normal, fire, water, grass, electric, ice, fighting, poison,
    ground, flying, psychic, bug, rock, ghost, dragon, dark, steel, fairy
};

const string eleType[18] = {
    "normal", "fire", "water", "grass", "electric", "ice", "fighting", "poison",
    "ground", "flying", "psychic", "bug", "rock", "ghost", "dragon", "dark", "steel", "fairy"
};



#ifndef __MOVES_H__
#define __MOVES_H__

class Move
{
public:
    Move( );
    Move( string moveName, int moveType, int moveElement, int moveAccuracy, int movePower );
    ~Move( );
    void printStats( );

    string name;
    int type;
    int element;
    int accuracy;
    int power;
};

#endif



inline Move::Move( )
{
    name = "";
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



inline void Move::printStats( )
{
    string moveType;

    if ( type == 0 )
        moveType = "Special";
    else
        moveType = "Physical";


    cout << name << endl;
    cout << "Type: " << moveType << endl;
    cout << "Element: " << eleType[element] << endl;
    cout << "Accuracy: " << accuracy << endl;
    cout << "Power: " << power << endl;
}


/*normal moves*/
const Move swipe( "Swipe", 1, normal, 100, 20 );    //0

const Move kick( "Kick", 1, normal, 90, 30 );       //1

const Move cinder( "Cinder", 0, fire, 100, 30 );    //2

const Move dowse( "Dowse", 0, water, 100, 30 );     //3

const Move thorn( "Thorn", 1, grass, 100, 30 );     //4


const Move moveID[5] = { swipe, kick, cinder, dowse, thorn };