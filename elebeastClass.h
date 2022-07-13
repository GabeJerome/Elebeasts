#include <string>
#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <fstream>
#include "moves.h"

using namespace std;

class beast;

bool storeBeastDataBinary( );

bool getData( beast &newBeast, int beastID );


#ifndef __ELEBEAST_H__
#define __ELEBEAST_H__

struct LearnSet
{
    Move move;
    int moveLevel = 0;
    bool learned = false;
};

struct baseStats
{
    int ID;
    char name[16];
    int health;
    int defense;
    int spdefense;
    int attack;
    int spattack;
    int speed;
    int eleType1;
    int eleType2;
    short int evolveLevel;
    short int moveSet[50] = { 0 };
};


class beast
{
    //could add EXP yield (reference)-> https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_effort_value_yield
private:
    
    int experience;
    int currentStats[6];
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
        int spdef, int att, int spatt, int spd, int type1, int type2, 
        short int evolveLvl, short currEvo, const short int moves[] );
    beast( baseStats newBeast );
    beast( int level, int ID );
    ~beast( );
    bool fight( Move move, beast &opponent );
    bool runAway( beast &opponent );
    void levelUp( );
    void changeMove( int move, Move replaceWith );
    void changeName( string newName );
    void gainExp( beast &opponent );
    void evolve( );
    void changeBaseStats( beast &newBeast );
    void operator=( beast &newBeast );
    char nickName[16];
    Move move[4];
    void printMoves( );
    baseStats base;
    int currentHealth;

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

    void setExp( int exp ); //Needed for initializing new pokemon from file
};

#endif



inline beast::beast( )
{
    strcpy_s( nickName, 16, base.name );
    experience = 0;
    base.health = currentHealth = 0;
    currentHealth = base.health;
    base.defense = 0;
    base.spdefense = 0;
    base.attack = 0;
    base.spattack = 0;
    base.speed = 0;
    base.eleType1 = 0;
    base.eleType2 = -1;
    base.evolveLevel = 101;

    currentStats[0] = getMaxHP( );
    currentStats[1] = getDef( );
    currentStats[2] = getSpDef( );
    currentStats[3] = getAtt( );
    currentStats[4] = getSpAtt( );
    currentStats[5] = getSpeed( );
}



inline beast::beast( string name, int exp, int maxHP, int currHP, int def,
    int spdef, int att, int spatt, int spd, int type1, int type2,
    short int evolveLvl, short currEvo, const short int moves[] )
{

    strcpy_s( nickName, 16, base.name );
    experience = exp;

    base.health = maxHP;
    base.defense = def;
    base.spdefense = spdef;
    base.attack = att;
    base.spattack = spatt;
    base.speed = spd;
    base.eleType1 = type1;
    base.eleType2 = type2;

    currentStats[0] = getMaxHP( );
    currentStats[1] = getDef( );
    currentStats[2] = getSpDef( );
    currentStats[3] = getAtt( );
    currentStats[4] = getSpAtt( );
    currentStats[5] = getSpeed( );

    currentHealth = getMaxHP( );
    base.evolveLevel = evolveLvl;
    writeLearnSet( moves );

    changeMove( 0, learnSet[0].move );
    learnSet[0].learned = true;
}



inline beast::beast( baseStats newBeast )
{
    strcpy_s( nickName, 16, newBeast.name );
    experience = 0;

    base.health = newBeast.health;
    base.defense = newBeast.defense;
    base.spdefense = newBeast.spdefense;
    base.attack = newBeast.attack;
    base.spattack = newBeast.spattack;
    base.speed = newBeast.speed;
    base.eleType1 = newBeast.eleType1;
    base.eleType2 = newBeast.eleType2;

    currentStats[0] = getMaxHP( );
    currentStats[1] = getDef( );
    currentStats[2] = getSpDef( );
    currentStats[3] = getAtt( );
    currentStats[4] = getSpAtt( );
    currentStats[5] = getSpeed( );
    currentHealth = getMaxHP( );

    base.evolveLevel = newBeast.evolveLevel;
    writeLearnSet( newBeast.moveSet );

    changeMove( 0, learnSet[0].move );
    learnSet[0].learned = true;
}



inline beast::beast(int level, int ID )
{
    getData( *this, ID );

    currentHealth = getMaxHP( );
    experience = level * level * level;
    currentStats[0] = getMaxHP( );
    currentStats[1] = getDef( );
    currentStats[2] = getSpDef( );
    currentStats[3] = getAtt( );
    currentStats[4] = getSpAtt( );
    currentStats[5] = getSpeed( );

    writeLearnSet( base.moveSet );
    changeMove( 0, learnSet[0].move );
    learnSet[0].learned = true;
}



inline beast::~beast( )
{

}



inline void beast::writeLearnSet( const short int moves[] )
{
    int i, num;
    short int moveID = 0, moveLevel;
    LearnSet temp;
    Move newMove;


    for ( i = 0; i < 50 && moves[i] != 0; i++ )
    {
        num = moves[i];

        moveLevel = num & 127;
        num >>= 7;

        moveID = num & 511;
        if ( moveID < 0 || moveID > 5 )
        {
            cout << "Invalid move number for " << nickName << endl;
            cout << "Exiting..." << endl;
            return;
        }

        if ( moveLevel == 0 )
            temp.learned = true;
        else
            temp.learned = false;
        temp.moveLevel = moveLevel;

        getData( newMove, moveID );

        temp.move = newMove;

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
    if ( opponent.base.eleType2 == -1 )
        effectiveness = effectiveChart[move.element][opponent.base.eleType1];
    else
        effectiveness = effectiveChart[move.element][opponent.base.eleType1] * effectiveChart[move.element][opponent.base.eleType2];

    if ( effectiveness == 0 )
        cout << "It doesn't affect " << opponent.nickName << '.' << endl;
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







inline void beast::evolve( )
{
    beast newBeast;

    base.ID++;

    if ( !getData( newBeast, base.ID ) )
        return;

    changeBaseStats( newBeast );

    cout << nickName << " evoloved into " << base.name << '!' << endl;

    if ( strcmp( nickName, base.name ) != 0 )
        strcpy_s( nickName, 16, base.name );
    printLvlUpStats( );
}

inline void beast::changeBaseStats( beast &newBeast )
{
    base.health = newBeast.base.health;
    base.defense = newBeast.base.defense;
    base.spdefense = newBeast.base.spdefense;
    base.attack = newBeast.base.attack;
    base.spattack = newBeast.base.spattack;
    base.speed = newBeast.base.speed;
    base.eleType1 = newBeast.base.eleType1;
    base.eleType2 = newBeast.base.eleType2;
    base.evolveLevel = newBeast.base.evolveLevel;
}



inline void beast::operator=( beast &newBeast )
{
    int experience;
    int currentStats[6];
    vector<LearnSet> learnSet;

    int i;

    base.ID = newBeast.base.ID;
    strcpy_s( base.name, 16, newBeast.base.name );
    changeBaseStats( newBeast );

    for ( i = 0; i < 50; i++ )
        base.moveSet[i] = newBeast.base.moveSet[i];

    experience = newBeast.experience;
    
    for ( i = 0; i < 6; i++ )
        currentStats[i] = newBeast.currentStats[i];

    //Do nothing until learnSet is converted to non dynamic memory
    learnSet = newBeast.learnSet;
}



inline void beast::levelUp( )
{
    vector<LearnSet>::iterator itr;
    int option = -1;
    int level = getLevel();

    


    for ( itr = learnSet.begin(); itr < learnSet.end(); itr++ )
    {
        if ( ( *itr ).moveLevel != 0 && ( *itr ).moveLevel <= level && ( *itr ).learned == false )
        {
            cout << nickName << " can learn " << ( *itr ).move.name
                << "! What move do you want to replace? Enter 5 to not learn the move." << endl;

            printMoves( );

            while ( option < 1 || option > 5 )
            {
                cin >> option;
                if ( option < 1 || option > 4 )
                    cout << "Invalid input. Choose a move 1 - 5" << endl;
            }

            if ( option == 5 )
            {
                cout << ( *itr ).move.name << " was not learned." << endl;
                return;
            }

            changeMove( option - 1, ( *itr ).move );

            cout << endl << nickName << " has learned " << ( *itr ).move.name << '!' << endl;
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
    strcpy_s( nickName, 16, newName.c_str( ) );
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
    


    experience += ( ( expYield * oppLevel) / 5 ) *
        ( ( 2 * oppLevel + 10 ) / ( oppLevel + getLevel( ) + 10 ) );

    if ( getLevel( ) > level )
    {
        cout << nickName << " is now level " << getLevel( ) << '!' << endl;

        if ( getLevel() >= base.evolveLevel )
            evolve( );
        else
            printLvlUpStats( );

        levelUp( );
    }

    currentStats[0] = getMaxHP( );
    currentStats[1] = getDef( );
    currentStats[2] = getSpDef( );
    currentStats[3] = getAtt( );
    currentStats[4] = getSpAtt( );
    currentStats[5] = getSpeed( );
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
    return int(floor( .01 * ( 2 * base.health ) * getLevel( ) ) + getLevel( ) + 10);
}



inline int beast::getCurrHP( )
{
    return currentHealth;
}



inline int beast::getDef( )
{
    return int( floor( .01 * ( 2 * base.defense ) * getLevel( ) ) + 5 );
}



inline int beast::getSpDef( )
{
    return int( floor( .01 * ( 2 * base.spdefense ) * getLevel( ) ) + 5 );
}



inline int beast::getAtt( )
{
    return int( floor( .01 * ( 2 * base.attack ) * getLevel( ) ) + 5 );
}



inline int beast::getSpAtt( )
{
    return int( floor( .01 * ( 2 * base.spattack ) * getLevel( ) ) + 5 );
}



inline int beast::getSpeed( )
{
    return int( floor( .01 * ( 2 * base.speed ) * getLevel( ) ) + 5 );
}



inline string beast::getType( )
{
    int i;
    string type1;
    string element[18] = { "normal", "fire", "water", "grass", "electric",
        "ice", "fighting", "poison", "ground", "flying", "psychic", "bug",
        "rock", "ghost", "dragon", "dark", "steel", "fairy" };

    if ( base.eleType2 == -1 )
    {
        for ( i = 0; i < 18; i++ )
        {
            if ( i == base.eleType1 )
                return element[i];
        }
    }
    else
    {
        for ( i = 0; i < 18; i++ )
        {
            if ( i == base.eleType1 )
                type1 = element[i];
        }
        for ( i = 0; i < 18; i++ )
        {
            if ( i == base.eleType1 )
                return type1 + ' ' + element[i];
        }
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



inline void beast::setExp( int exp )
{
    experience = exp;

    currentStats[0] = getMaxHP( );
    currentStats[1] = getDef( );
    currentStats[2] = getSpDef( );
    currentStats[3] = getAtt( );
    currentStats[4] = getSpAtt( );
    currentStats[5] = getSpeed( );
}



//TODO: create more beasts and moves.
/*
Moves are stored as short integers.The first 7 bits represent the level that
the beast learns the move. The remaining 9 bits represent the number ID of the move
*/
