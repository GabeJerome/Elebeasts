#include <string>
#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include "moves.h"

using namespace std;

//FIGURE OUT HOW TO USE LEARNSETS

#ifndef __ELEBEAST_H__
#define __ELEBEAST_H__

class beast
{
    //could add EXP yield (reference)-> https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_effort_value_yield
private:
    int level;
    int experience;
    int baseHealth;
    int currentHealth;
    int baseDefense;
    int baseSpdefense;
    int baseAttack;
    int baseSpattack;
    int baseSpeed;
    int eleType;
    vector<Move> learnSet;    //USE
    int lvlProgression[100] =
            /* 0       1       2       3       4       5       6       7       8       9*/
        /*0*/        { 0,      8,      27,     64,     125,    216,    343,    512,    729,
        /*1*/  1000,   1331,   1728,   2197,   2744,   3375,   4096,   4913,   5832,   6859,
        /*2*/  8000,   9261,   10648,  12167,  13824,  15625,  17576,  19683,  21952,  24389,
        /*3*/  27000,  29791,  32768,  35937,  39304,  42875,  46656,  50653,  54872,  59319,
        /*4*/  64000,  68921,  74088,  79507,  85184,  91125,  97336,  103823, 110592, 117649,
        /*5*/  125000, 132651, 140608, 148877, 157464, 166375, 175616, 185193, 195112, 205379,
        /*6*/  216000, 226981, 238328, 250047, 262144, 274625, 287496, 300763, 314432, 328509,
        /*7*/  343000, 357911, 373248, 389017, 405224, 421875, 438976, 456533, 474552, 493039,
        /*8*/  512000, 531441, 551368, 571787, 592704, 614125, 636056, 658503, 681472, 704969,
        /*9*/  729000, 753571, 778688, 804357, 830584, 857375, 884736, 912673, 941192, 970299,
        /*10*/ 1000000 };

public:
    beast( );
    beast( string name, int exp, int maxHP, int currHP, int def,
        int spdef, int att, int spatt, int spd, int type );
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
    level = 0;
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
    int spdef, int att, int spatt, int spd, int type )
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
    level = getLevel( );
    currentHealth = getMaxHP( );
}



inline beast::~beast( )
{

}


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
    double effectiveChart[18][18] =
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

    if ( getSpeed( ) >= opponent.getSpeed( ) )
    {
        attemptNum = 1;
        return true;
    }

    odds = ( ( ( getSpeed( ) * 32 ) / ( ( opponent.getSpeed( ) / 4 ) % 256 ) ) + 30 * attemptNum );

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
    if ( level == getLevel( ) )
        return false;


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
    int expYield = ( rand( ) % 100 ) + 60;

    experience += ( ( expYield * opponent.level ) / 5 ) *
        ( ( 2 * opponent.level + 10 ) / ( opponent.level + level + 10 ) );
}



inline int beast::getLevel( )
{
    int i;

    if ( experience < 8 )
        return 1;

    for ( i = level - 1; i < 100; i++ )
    {
        if ( experience >= lvlProgression[i] )
            level = i + 1;
        else
            return level;
    }

    return 100;
}



inline int beast::getExp( )
{
    return experience;
}



inline int beast::getMaxHP( )
{
    return int(floor( .01 * ( 2 * baseHealth ) * level ) + level + 10);
}



inline int beast::getCurrHP( )
{
    return currentHealth;
}



inline int beast::getDef( )
{
    return int( floor( .01 * ( 2 * baseDefense ) * level ) + 5 );
}



inline int beast::getSpDef( )
{
    return int( floor( .01 * ( 2 * baseSpdefense ) * level ) + 5 );
}



inline int beast::getAtt( )
{
    return int( floor( .01 * ( 2 * baseAttack ) * level ) + 5 );
}



inline int beast::getSpAtt( )
{
    return int( floor( .01 * ( 2 * baseSpattack ) * level ) + 5 );
}



inline int beast::getSpeed( )
{
    return int( floor( .01 * ( 2 * baseSpeed ) * level ) + 5 );
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



//TODO: test runAway function, create more beasts and moves.

const beast Flacora( "Flacora", 0, 40, 40, 45, 48, 53, 60, 65, fire );
/*vector<Move> FlacoraLearnSet =  { kick, cinder };
vector<int> learnSetLevel = { 3, 6 };*/

const beast Stropie( "Stropie", 0, 45, 45, 60, 59, 46, 48, 45, water );

const beast Fotosin( "Fotosin", 0, 43, 43, 50, 64, 50, 63, 43, grass );