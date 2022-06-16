#include <string>
#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include "moves.h"

using namespace std;



#ifndef __ELEBEAST_H__
#define __ELEBEAST_H__

struct LearnSet
{
    Move move;
    int moveLevel = 0;
};


class beast
{
    //could add EXP yield (reference)-> https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_effort_value_yield
private:
    //int level;
    int experience;
    int baseHealth;
    int currentHealth;
    int baseDefense;
    int baseSpdefense;
    int baseAttack;
    int baseSpattack;
    int baseSpeed;
    int eleType;
    LearnSet *learnSet = nullptr;
    void writeLearnSet( int setSize, const int moves[] );

public:
    beast( );
    beast( string name, int exp, int maxHP, int currHP, int def,
        int spdef, int att, int spatt, int spd, int type, int setSize, const int learnSet[] );
    ~beast( );
    bool fight( Move move, beast &opponent );
    bool runAway( beast &opponent );
    void heal( string healer );
    bool levelup( );    //TODO: write levelup
    void changeMove( int move, Move replaceWith );
    void changeName( string newName );
    void gainExp( beast &opponent );
    string beastName;
    Move move[4];

    int getLevel( );
    int getExp( );
    int getMaxHP( );
    int getCurrHP( );
    int getDef( );
    int getSpDef( );
    int getAtt( );
    int getSpAtt( );
    int getSpeed( );
    string getType( );
    void printStats( ); //TODO: write function
};

#endif



inline beast::beast( )
{
    beastName = "";
    experience = 0;
    baseHealth = currentHealth = 0;
    currentHealth = baseHealth;
    baseDefense = 0;
    baseSpdefense = 0;
    baseAttack = 0;
    baseSpattack = 0;
    baseSpeed = 0;
    eleType = 0;
}

inline beast::beast( string name, int exp, int maxHP, int currHP, int def,
    int spdef, int att, int spatt, int spd, int type, int setSize, const int moves[] )
{

    beastName = name;
    experience = exp;
    baseHealth = maxHP;
    baseDefense = def;
    baseSpdefense = spdef;
    baseAttack = att;
    baseSpattack = spatt;
    baseSpeed = spd;
    eleType = type;
    currentHealth = getMaxHP( );
    writeLearnSet( setSize, moves );

    changeMove( 0, learnSet[0].move );
}



inline beast::~beast( )
{

}



inline void beast::writeLearnSet( int setSize, const int moves[] )
{
    int i, num;
    short int moveNum = 0, moveLevel;

    learnSet = new ( nothrow ) LearnSet[setSize];
    if ( learnSet == nullptr )
    {
        cout << "Could not allocate memory for learnSet." << endl;
        return;
    }

    for ( i = 0; i < setSize; i++ )
    {
        num = moves[i];

        moveLevel = num & 127;
        num >>= 7;

        moveNum = num & 511;
        if ( moveNum < 0 || moveNum > 4 )
        {
            cout << "Invalid move number for " << beastName << endl;
            cout << "Exiting..." << endl;
            return;
        }

        learnSet[i].moveLevel = moveLevel;
        learnSet[i].move = allMoves[moveNum];
    }
}



const double effectiveChart[18][18] =
{                  /* 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17*/
    /*Normal   0*/  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,.5 , 0 , 1 , 1 ,.5 , 1 },
    /*Fire     1*/  { 1 ,.5 ,.5 , 2 , 1 , 2 , 1 , 1 , 1 , 1 , 1 , 2 ,.5 , 1 ,.5 , 1 , 2 , 1 },
    /*Water    2*/  { 1 , 2 ,.5 ,.5 , 1 , 1 , 1 ,.5 , 2 ,.5 , 1 ,.5 , 2 , 1 ,.5 , 1 , 1 , 1 },
    /*Grass    3*/  { 1 ,.5 , 2 ,.5 , 1 , 1 , 1 ,.5 , 2 ,.5 , 1 ,.5 , 2 , 1 ,.5 , 1 ,.5 , 1 },
    /*Electric 4*/  { 1 , 1 , 2 ,.5 ,.5 , 1 , 1 , 1 , 0 , 2 , 1 , 1 , 1 , 1 ,.5 , 1 , 1 , 1 },
    /*Ice      5*/  { 1 ,.5 ,.5 , 2 , 1 ,.5 , 1 , 1 , 2 , 2 , 1 , 1 , 1 , 1 , 2 , 1 ,.5 , 1 },
    /*Fighting 6*/  { 2 , 1 , 1 , 1 , 1 , 2 , 1 ,.5 , 1 ,.5 ,.5 ,.5 , 2 , 0 , 1 , 2 , 2 ,.5 },
    /*Poison   7*/  { 1 , 1 , 1 , 2 , 1 , 1 , 1 ,.5 ,.5 , 1 , 1 , 1 ,.5 ,.5 , 1 , 1 , 0 , 2 },
    /*Ground   8*/  { 1 , 2 , 1 ,.5 , 2 , 1 , 1 , 2 , 1 , 0 , 1 ,.5 , 2 , 1 , 1 , 1 , 2 , 1 },
    /*Flying   9*/  { 1 , 1 , 1 , 2 ,.5 , 1 , 2 , 1 , 1 , 1 , 1 , 2 ,.5 , 1 , 1 , 1 ,.5 , 1 },
    /*Psychic  10*/ { 1 , 1 , 1 , 1 , 1 , 1 , 2 , 2 , 1 , 1 ,.5 , 1 , 1 , 1 , 1 , 0 ,.5 , 1 },
    /*Bug      11*/ { 1 ,.5 , 1 , 2 , 1 , 1 ,.5 ,.5 , 1 ,.5 , 2 , 1 , 1 ,.5 , 1 , 2 ,.5 ,.5 },
    /*Rock     12*/ { 1 , 2 , 1 , 1 , 1 , 2 ,.5 , 1 ,.5 , 2 , 1 , 2 , 1 , 1 , 1 , 1 ,.5 , 1 },
    /*Ghost    13*/ { 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 1 , 1 , 2 , 1 ,.5 , 1 , 1 },
    /*Dragon   14*/ { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 1 ,.5 , 0 },
    /*Dark     15*/ { 1 , 1 , 1 , 1 , 1 , 1 ,.5 , 1 , 1 , 1 , 2 , 1 , 1 , 2 , 1 ,.5 , 1 ,.5 },
    /*Steel    16*/ { 1 ,.5 ,.5 , 1 ,.5 , 2 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 1 , 1 , 1 ,.5 , 2 },
    /*Fairy    17*/ { 1 ,.5 , 1 , 1 , 1 , 1 , 2 ,.5 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 2 ,.5 , 1 }
};

inline bool beast::fight( Move move, beast &opponent )
{
    random_device rand;
    random_device roll;
    int hit = ( rand( ) % 100 ) + 1;

    if ( hit > move.accuracy )
        return false;

    double randRoll = ( double( ( roll( ) % 15 ) + 1 ) / 100 ) + .85;
    int damage;
    int Def, Att;
    double critical = 1;
    double effectiveness;

    //calculate effectiveness
    effectiveness = effectiveChart[move.element][opponent.eleType];

    if ( effectiveness == 0 )
        cout << "It doesn't affect " << opponent.beastName << '.' << endl;
    else if ( effectiveness == .5 )
        cout << "It's not very effective." << endl;
    else if ( effectiveness == 2 )
        cout << "It's super effective!" << endl;


    //TODO: add comments


    if ( hit < 5 )
        critical = 1.5;

    if ( move.type == 0 )
    {
        Def = opponent.getSpDef( );
        Att = getSpAtt( );
    }
    else
    {
        Def = opponent.getDef( );
        Att = getAtt( );
    }

    damage = int( ( ( ( ( ( ( static_cast<double>( 2 ) * getLevel( ) ) / 5 ) + 2 ) * move.power
        * Att / Def ) / 50 ) + 2 ) * randRoll * critical * effectiveness );

    opponent.currentHealth -= damage;

    if ( opponent.currentHealth < 0 )
        opponent.currentHealth = 0;

    return true;
}



inline bool beast::runAway( beast &opponent )
{
    int odds, run;
    random_device rand;
    static int attemptNum = 1;
    int mySpeed = getSpeed( );
    int oppSpeed = opponent.getSpeed( );

    if ( mySpeed >= oppSpeed )
    {
        attemptNum = 1;
        return true;
    }

    odds = ( ( ( mySpeed * 32 ) / ( ( oppSpeed / 4 ) % 256 ) ) + 30 * attemptNum );

    run = rand( ) % 256;

    if ( odds > 255 || run < odds )
    {
        attemptNum = 1;
        return true;
    }

    attemptNum++;

    return false;
}



inline void beast::heal( string healer )
{
    if ( currentHealth == 0 )
    {
        cout << "This beast needs to be revived first!" << endl;
        return;
    }

    if ( healer == "small" )
        currentHealth += 15;
    else if ( healer == "medium" )
        currentHealth += 25;
    else if ( healer == "large" )
        currentHealth += 40;

    if ( currentHealth > getMaxHP( ) )
        currentHealth = getMaxHP( );
}

inline bool beast::levelup( )
{
    
    //TODO: WRITE THIS FUNCTION!!!

}



inline void beast::changeMove( int moveNum, Move replaceWith )
{
    move[moveNum] = replaceWith;
}



inline void beast::changeName( string newName )
{
    beastName = newName;
}

inline void beast::gainExp( beast &opponent )
{
    random_device rand;
    int oppLevel = opponent.getLevel( );
    int expYield = ( rand( ) % 100 ) + 60;

    experience += ( ( expYield * oppLevel) / 5 ) *
        ( ( 2 * oppLevel + 10 ) / ( oppLevel + getLevel( ) + 10 ) );
}



inline int beast::getLevel( )
{
    if ( experience < 8 )
        return 1;
    if ( experience > 1000000 )
        return 100;

    return int( cbrt( experience ) );
}



inline int beast::getExp( )
{
    return experience;
}



inline int beast::getMaxHP( )
{
    return int(floor( .01 * ( 2 * baseHealth ) * getLevel( ) ) + getLevel( ) + 10);
}



inline int beast::getCurrHP( )
{
    return currentHealth;
}



inline int beast::getDef( )
{
    return int( floor( .01 * ( 2 * baseDefense ) * getLevel( ) ) + 5 );
}



inline int beast::getSpDef( )
{
    return int( floor( .01 * ( 2 * baseSpdefense ) * getLevel( ) ) + 5 );
}



inline int beast::getAtt( )
{
    return int( floor( .01 * ( 2 * baseAttack ) * getLevel( ) ) + 5 );
}



inline int beast::getSpAtt( )
{
    return int( floor( .01 * ( 2 * baseSpattack ) * getLevel( ) ) + 5 );
}



inline int beast::getSpeed( )
{
    return int( floor( .01 * ( 2 * baseSpeed ) * getLevel( ) ) + 5 );
}



inline string beast::getType( )
{
    int i;
    string element[18] = { "normal", "fire", "water", "grass", "electric",
        "ice", "fighting", "poison", "ground", "flying", "psychic", "bug",
        "rock", "ghost", "dragon", "dark", "steel", "fairy" };

    for ( i = 0; i < 18; i++ )
    {
        if ( i == eleType )
            return element[i];
    }

    return "ERROR";
}



//TODO: create more beasts and moves.

const int flacoraLearnSet[2] = { 0, 261 };
const beast Flacora( "Flacora", 0, 40, 40, 45, 48, 53, 60, 65, fire, 2, flacoraLearnSet );

const int stropieLearnSet[2] = { 128, 389 };
const beast Stropie( "Stropie", 0, 45, 45, 60, 59, 46, 48, 45, water, 2, stropieLearnSet );

const int fotosinLearnSet[2] = { 0, 517 };
const beast Fotosin( "Fotosin", 0, 43, 43, 50, 64, 50, 63, 43, grass, 2, fotosinLearnSet );