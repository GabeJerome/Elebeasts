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
    bool learned = false;
};


class beast: private Move
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
    int currentStats[6];
    int eleType;
    //LearnSet *learnSet = nullptr;
    vector<LearnSet> learnSet;
    void writeLearnSet( const short int moves[] );
    int lvlProgression[100] =
            /* 0       1       2       3       4       5       6       7       8       9*/
        /*0*/ {        0,      8,      27,     64,     125,    216,    343,    512,    729,
        /*1*/  1000,   1331,   1728,   2197,   2744,   3375,   4096,   4913,   5832,   6859,
        /*2*/  8000,   9261,   10648,  12167,  13824,  15625,  17576,  19683,  21952,  24389,
        /*3*/  27000,  29791,  32768,  35937,  39304,  42875,  46656,  50653,  54872,  59319,
        /*4*/  64000,  68921,  74088,  79507,  85184,  91125,  97336,  103823, 110592, 117649,
        /*5*/  125000, 132651, 140608, 148877, 157464, 166375, 175616, 185193, 195112, 205379,
        /*6*/  216000, 226981, 238328, 250047, 262144, 274625, 287496, 300763, 314432, 328509,
        /*7*/  343000, 357911, 373248, 389017, 405224, 421875, 438976, 456533, 474552, 493039,
        /*8*/  512000, 531441, 551368, 571787, 592704, 614125, 636056, 658503, 681472, 704969,
        /*9*/  729000, 753571, 778688, 804357, 830584, 857375, 884736, 912673, 941192, 970299,
        /*10*/ 1000000
              };

public:
    beast( );
    beast( string name, int exp, int maxHP, int currHP, int def,
        int spdef, int att, int spatt, int spd, int type, const short int moves[] );
    ~beast( );
    bool fight( Move move, beast &opponent );
    bool runAway( beast &opponent );
    void heal( string healer );
    void levelUp( );    //TODO: write levelup
    void changeMove( int move, Move replaceWith );
    void changeName( string newName );
    void gainExp( beast &opponent );
    string beastName;
    Move move[4];
    void printMoves( );

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
    void printStats( );
    void printLvlUpStats( );
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
    int spdef, int att, int spatt, int spd, int type, const short int moves[] )
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
    writeLearnSet( moves );

    changeMove( 0, learnSet[0].move );
    learnSet[0].learned = true;
}



inline beast::~beast( )
{

}



inline void beast::writeLearnSet( const short int moves[] )
{
    int i, num;
    short int moveNum = 0, moveLevel;
    LearnSet temp;


    for ( i = 0; i < 50; i++ )
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

        if ( temp.moveLevel == 0 )
            temp.learned = true;
        temp.moveLevel = moveLevel;
        temp.move = moveID[moveNum];

        learnSet.push_back( temp );
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

inline void beast::levelUp( )
{
    vector<LearnSet>::iterator itr;
    int option = -1;
    int level = getLevel();

    printLvlUpStats( );

    for ( itr = learnSet.begin(); itr < learnSet.end(); itr++ )
    {
        if ( (*itr).moveLevel <= level && ( *itr ).learned == false )
        {
            cout << beastName << " can learn " << (*itr).move.name
                << "! What move do you want to replace?" << endl;

            printMoves( );

            while ( option < 1 || option > 4 )
            {
                cin >> option;
                if ( option < 1 || option > 4 )
                    cout << "Invalid input. Choose a move 1 - 4" << endl;
            }

            changeMove( option - 1, (*itr).move );
            
            cout << endl << beastName << " has learned " << (*itr).move.name << '!' << endl;
            printMoves( );

            ( *itr ).learned = true;
        }
    }
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
    int expYieldRange = 80;
    random_device rand;
    int level = getLevel( );
    int oppLevel = opponent.getLevel( );
    int expYield = ( rand( ) % expYieldRange ) + 60;
    
    //store original stats in case of level up
    //needed for display
    currentStats[0] = getMaxHP( );
    currentStats[1] = getDef( );
    currentStats[2] = getSpDef( );
    currentStats[3] = getAtt( );
    currentStats[4] = getSpAtt( );
    currentStats[5] = getSpeed( );


    experience += ( ( expYield * oppLevel) / 5 ) *
        ( ( 2 * oppLevel + 10 ) / ( oppLevel + getLevel( ) + 10 ) );

    if ( getLevel( ) > level )
    {
        cout << beastName << " is now level " << getLevel( ) << '!' << endl;
        levelUp( );
    }
}



inline void beast::printMoves( )
{
    int i;

    for ( i = 0; i < 4; i++ )
    {
        cout << "Move " << i + 1 << ": " << move[i].name << endl;
    }
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



inline void beast::printStats( )
{
    cout << "HP:          " << getMaxHP( ) << endl;
    cout << "Defense:     " << getDef( ) << endl;
    cout << "Sp Defense:  " << getSpDef( ) << endl;
    cout << "Attack:      " << getAtt( ) << endl;
    cout << "Sp Attack:   " << getSpAtt( ) << endl;
    cout << "Speed:       " << getSpeed( ) << endl;
}

inline void beast::printLvlUpStats( )
{
    cout << "HP:          " << currentStats[0] << " + " << getMaxHP( ) - currentStats[0] << endl;
    cout << "Defense:     " << currentStats[1] << " + " << getDef( ) - currentStats[1] << endl;
    cout << "Sp Defense:  " << currentStats[2] << " + " << getSpDef( ) - currentStats[2] << endl;
    cout << "Attack:      " << currentStats[3] << " + " << getAtt( ) - currentStats[3] << endl;
    cout << "Sp Attack:   " << currentStats[4] << " + " << getSpAtt( ) - currentStats[4] << endl;
    cout << "Speed:       " << currentStats[5] << " + " << getSpeed( ) - currentStats[5] << endl;
}



//TODO: create more beasts and moves.
/*
Moves are stored as short integers.The first 7 bits represent the level that
the beast learns the move. The remaining 9 bits represent the number ID of the move
*/

const short int flacoraLearnSet[50] = { 0, 261, 0 };
const beast Flacora( "Flacora", 0, 40, 40, 45, 48, 53, 60, 65, fire, flacoraLearnSet );

const short int stropieLearnSet[50] = { 128, 389, 0 };
const beast Stropie( "Stropie", 0, 45, 45, 60, 59, 46, 48, 45, water, stropieLearnSet );

const short int fotosinLearnSet[50] = { 0, 517, 0 };
const beast Fotosin( "Fotosin", 0, 43, 43, 50, 64, 50, 63, 43, grass, fotosinLearnSet );