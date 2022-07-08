#pragma once
#include <string>
#include <iomanip>

using namespace std;



class Move;

bool storeMoveDataBinary( );

bool getData( Move &newMove, int moveID );

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

    char name[20];
    int type;
    int element;
    int accuracy;
    int power;
};

#endif



inline Move::Move( )
{
    strcpy_s( name, "" );
    type = 0;
    element = 0;
    accuracy = 0;
    power = 0;
}


inline Move::Move( string moveName, int moveType, int moveElement, int moveAccuracy,
    int movePower )
{
    int i;

    for ( i = 0; i < moveName.size( ); i++ )
        name[i] = moveName[i];
    for ( i = i; i < 20; i++ )
        name[i] = '\0';
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