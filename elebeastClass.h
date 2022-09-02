/** **************************************************************************
* @file
*
* @brief Beast class
** ****************************************************************************/

#pragma once
#include <string>
#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <fstream>
#include <thread>
#include "moves.h"

using namespace std;

class beast;

bool storeBeastDataBinary( );

bool getData( beast &newBeast, int beastID );


#ifndef __ELEBEAST_H__
#define __ELEBEAST_H__

/**
* @brief Holds data for a single move in a beast's learn set.
*/
struct LearnSet
{
    Move move;              /**< The move that the beast will learn. */
    int moveLevel = 0;      /**< The level that the beast will learn the move. */
    bool learned = false;   /**< Boolean indicating if the move has been learned. */
};

/**
* @brief Holds the beast's base stats.
*/
struct baseStats
{
    int ID;                         /**< The beast's ID to locate in data storage. */
    char name[16];                  /**< The beast's original name. */
    int health;                     /**< base health. */
    int defense;                    /**< base defense. */
    int spdefense;                  /**< base special defense. */
    int attack;                     /**< base attack. */
    int spattack;                   /**< base special attack. */
    int speed;                      /**< base speed. */
    int eleType1;                   /**< The beast's first elemental type. */
    int eleType2;                   /**< The beast's second elemental type. (-1 = no type) */
    short int evolveLevel;          /**< The level that the beast evolves at. (101 if the beast doesn't evolve) */
    short int moveSet[30] = { 0 };  /**< An array of the moves that the beast will learn as it levels up. */
};


/**
* @brief Beast class used in the trainer class. 
*/
class beast
{
private:
    int experience;
    int currentStats[6];
    LearnSet learnSet[30];

public:
    char nickName[16];
    Move move[4];
    baseStats base;
    int currentHealth;

    beast( );
    beast( string name, int exp, int maxHP, int currHP, int def,
        int spdef, int att, int spatt, int spd, int type1, int type2,
        short int evolveLvl, const short int moves[] );
    beast( baseStats newBeast );
    beast( int level, int ID );
    ~beast( );
    bool attack( Move move, beast &opponent, bool enemy = false );
    bool runAway( beast &opponent );
    void levelUp( );
    void changeMove( int move, Move replaceWith );
    void changeName( string newName );
    void gainExp( beast &opponent, int yield = 1 );
    void evolve( );
    void changeBaseStats( beast &newBeast );
    void operator=( beast &newBeast );
    void writeLearnSet( const short int moves[] );
    void learnMoves( );


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
    int getBaseStatTotal( );
    void printStats( );
    void printLvlUpStats( );
    void printMoves( );
    void printOverview( );
    void setExp( int exp );

    int lvlProgression[100] =
    {
        /* 0       1       2       3       4       5       6       7       8       9*/
        /*0*/   0,      8,      27,     64,     125,    216,    343,    512,    729,
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
};

#endif



/** ***************************************************************************
* @author Gabe Jerome
*
* @par Description
* This is the default constructor for the beast class. It sets all of the
* beast's base values to zero. It is used to create null beasts that are
* meant to be used as place holders.
*
* @param[in] none
*
* @returns nothing
*
* @par Example
* @verbatim
    beast testBeast;
  @endverbatim
* ****************************************************************************/
inline beast::beast( )
{
    int i;

    base.ID = -1;
    
    //copy nickname
    for ( i = 0; i < 16; i++ )
        nickName[i] = base.name[i];

    //set base stats
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

    //set current stats for printing
    currentStats[0] = getMaxHP( );
    currentStats[1] = getDef( );
    currentStats[2] = getSpDef( );
    currentStats[3] = getAtt( );
    currentStats[4] = getSpAtt( );
    currentStats[5] = getSpeed( );
}



/** ***************************************************************************
* @author Gabe Jerome
*
* @par Description
* This is the custom constructor for the beast class. It has many parameters
* that set the base values of the beast. It is meant for creating beasts with
* custom stats for testing.
*
* @param[in] name The name of the beast.
* @param[in] exp The experience that the beast will have.
* @param[in] maxHP The max health that the beast will have.
* @param[in] currHP The current health that the beast will have.
* @param[in] def The base defense that the beast will have.
* @param[in] spdef The base special defense that the beast will have.
* @param[in] att The base attack that the beast will have.
* @param[in] spatt The base special attack that the beast will have.
* @param[in] spd The base speed that the beast will have.
* @param[in] type1 The beast's first element.
* @param[in] type2 The beast's second element. This may be empty.
* @param[in] evolveLvl The levle that the beast will evolve.
* @param[in] moves A set of numbers representing the moves that the beast
*               can learn.
*
* @returns nothing
*
* @par Example
* @verbatim
    beast testBeast( "Flacora", 111, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, flacoraLearnSet );
  @endverbatim
* ****************************************************************************/
inline beast::beast( string name, int exp, int maxHP, int currHP, int def,
    int spdef, int att, int spatt, int spd, int type1, int type2,
    short int evolveLvl, const short int moves[] )
{
    int i;

    //copy nickname
    for ( i = 0; i < 16; i++ )
        nickName[i] = base.name[i];
    experience = exp;

    //set base stats
    base.health = maxHP;
    base.defense = def;
    base.spdefense = spdef;
    base.attack = att;
    base.spattack = spatt;
    base.speed = spd;
    base.eleType1 = type1;
    base.eleType2 = type2;

    //set current stats for printing
    currentStats[0] = getMaxHP( );
    currentStats[1] = getDef( );
    currentStats[2] = getSpDef( );
    currentStats[3] = getAtt( );
    currentStats[4] = getSpAtt( );
    currentStats[5] = getSpeed( );
    currentHealth = getMaxHP( );
    base.evolveLevel = evolveLvl;

    //write learnset from moves
    writeLearnSet( moves );

    //learn appropriate moves at given level
    learnMoves( );
}



/** ***************************************************************************
* @author Gabe Jerome
*
* @par Description
* This is a constructor that copies the inputted beast. It is meant for
* creating copies of beasts when generating random ones.
*
* @param[in] newBeast Beast that will be copied.
*
* @returns nothing
*
* @par Example
* @verbatim
    beast testBeast1( "Flacora", 111, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, flacoraLearnSet );
    beast testBeast2( testBeast1 );
* @endverbatim
******************************************************************************/
inline beast::beast( baseStats newBeast )
{
    int i;

    //copy nickname
    for ( i = 0; i < 16; i++ )
        nickName[i] = base.name[i];
    experience = 0;

    //set base stats
    base.health = newBeast.health;
    base.defense = newBeast.defense;
    base.spdefense = newBeast.spdefense;
    base.attack = newBeast.attack;
    base.spattack = newBeast.spattack;
    base.speed = newBeast.speed;
    base.eleType1 = newBeast.eleType1;
    base.eleType2 = newBeast.eleType2;

    //set current stats for printing
    currentStats[0] = getMaxHP( );
    currentStats[1] = getDef( );
    currentStats[2] = getSpDef( );
    currentStats[3] = getAtt( );
    currentStats[4] = getSpAtt( );
    currentStats[5] = getSpeed( );
    currentHealth = getMaxHP( );
    base.evolveLevel = newBeast.evolveLevel;

    //write learnset from moves
    writeLearnSet( newBeast.moveSet );

    //learn appropriate moves at given level
    learnMoves( );
}



/** ***************************************************************************
* @author Gabe Jerome
*
* @par Description
* This is a test constructor. It will retrieve data for a beast and set it to
* a desired level.
*
* @param[in] level The desired level of the new beast.
* @param[in] ID The ID number of the desired beast.
*
* @returns nothing
*
* @par Example
* @verbatim
    beast testBeast( 23, 2 );
    //testBeast is a level 23 Firectric
* @endverbatim
******************************************************************************/
inline beast::beast(int level, int ID )
{
    //retrieve beast data from file
    getData( *this, ID );
    
    //set experience using level
    experience = level * level * level;
    currentHealth = getMaxHP( );
    
    //set current stats for printing
    currentStats[0] = getMaxHP( );
    currentStats[1] = getDef( );
    currentStats[2] = getSpDef( );
    currentStats[3] = getAtt( );
    currentStats[4] = getSpAtt( );
    currentStats[5] = getSpeed( );

    //write learnset from moves
    writeLearnSet( base.moveSet );
    
    //learn appropriate moves at given level
    learnMoves( );
}



/** ***************************************************************************
* @author Gabe Jerome
*
* @par Description
* This is the deconstructor for the beast class. There is no dynamic memory
* in this class that needs to be cleared.
*
* @param[in] none
*
* @returns nothing
*
* @par Example
* @verbatim
* int main( )
* {
      beast sampleBeast;
  }
  //The deconstructor is called when the instance goes out of scope
  @endverbatim
* ****************************************************************************/
inline beast::~beast( )
{
    //no dynamic memory
}



/** ***************************************************************************
* @author Gabe Jerome
*
* @par Description
* This function writes the learn set for the beast. It takes in an array of
* short integers that represent the moves. The first 7 bits are the level that
* the beast learns the move. The remaining 9 bits are the ID of the move. It
* stores these values and populates the array of learnest structs for the
* beast. This function is called in the constructors for the class.
*
* @param[in] moves The array of short integers that hold move data
*
* @returns nothing
*
* @par Example
* @verbatim
inline beast::beast(int level, int ID )
{
    getData( *this, ID );
    
    experience = level * level * level;
    currentHealth = getMaxHP( );
    
    currentStats[0] = getMaxHP( );
    currentStats[1] = getDef( );
    currentStats[2] = getSpDef( );
    currentStats[3] = getAtt( );
    currentStats[4] = getSpAtt( );
    currentStats[5] = getSpeed( );

    writeLearnSet( base.moveSet );
    
    learnMoves( );
}
* @endverbatim
******************************************************************************/
inline void beast::writeLearnSet( const short int moves[] )
{
    int i, num;
    short int moveID = 0, moveLevel;
    LearnSet temp;
    Move newMove;

    //loop for each move until move is empty
    for ( i = 0; i < 30 && moves[i] != 0; i++ )
    {
        //set number to be unpacked
        num = moves[i];

        //get move level from the first 7 bits
        moveLevel = num & 127;

        //shift packed number down
        num >>= 7;

        //get moveID from remaining 9 bits
        moveID = num & 511;

        //check to see if the move exists
        if ( moveID < 0 || moveID > 5 )
        {
            cout << "Invalid move number for " << nickName << endl;
            cout << "Exiting..." << endl;
            return;
        }

        //set level 0 moves to learned
        if ( moveLevel == 0 )
            temp.learned = true;
        else
            temp.learned = false;

        //record move level in temporary learnset
        temp.moveLevel = moveLevel;

        //get the data from the move using the move ID
        getData( newMove, moveID );

        //store the move stats in temporary learnset
        temp.move = newMove;

        //put the temporary move into the beast's learnset
        learnSet[i] = temp;
    }
}



/**
* @brief Effectiveness chart for reference in the attack function
*/
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



/** ***************************************************************************
* @author Gabe Jerome
*
* @par Description
* This is the attack function that is called in battle. It determines if a move
* hits and if it is a critical hit. If it hits, it calculates the elemental
* effectiveness of the move and the damage it does based on the active defense
* and attack (physical or special).
*
* @param[in] move The move that the attacking beast is using.
* @param[in, out] opponent The beast that is being attacked.
* @param[in] enemy Tells whether the attacker is the player or the enemy.
*                   used for printing names to the screen.
*
* @returns True if the attack hits. False if the attack misses.
*
* @par Example
* @verbatim
    trainer player;
    cin >> input;

    player.party[currBeast].attack( player.party[currBeast].move[input - 1], player.currOpponent );
* @endverbatim
******************************************************************************/
inline bool beast::attack( Move move, beast &opponent, bool enemy )
{
    random_device rand;
    int hit;
    string oppName = opponent.nickName, name = this->nickName;
    double randRoll;
    int damage;
    int Def, Att;
    double critical = 1;
    double effectiveness;

    //generate a random number between 0 and 100
    hit = ( rand( ) % 100 ) + 1;

    //set foe prefix to appropriate name
    if ( enemy )
        name = "Foe " + name;
    else
        oppName = "Foe " + oppName;

    //print usage statement with time buffer around it.
    this_thread::sleep_for( chrono::seconds( 1 ) );
    cout << name << " used " << move.name << '.' << endl;
    this_thread::sleep_for( chrono::seconds( 2 ) );

    //if hit is strictly greater than the move, then the move misses and return
    if ( hit > move.accuracy )
    {
        //display miss message and exit function
        cout << name << " missed." << endl << endl;
        this_thread::sleep_for( chrono::seconds( 1 ) );
        return false;
    }

    //calculate the random role damage multiplier (between .85 and 1)
    randRoll = ( double( ( rand( ) % 15 ) + 1 ) / 100 ) + .85;
    
    //calculate elemental effectiveness with one type or two types
    if ( opponent.base.eleType2 == -1 )
        effectiveness = effectiveChart[move.element][opponent.base.eleType1];
    else
        effectiveness = effectiveChart[move.element][opponent.base.eleType1]
        * effectiveChart[move.element][opponent.base.eleType2];

    //display messages for no effect, half damage, or double damage
    //no message is needed for normal damage
    if ( effectiveness == 0 )
        cout << "It doesn't affect " << oppName << '.' << endl;
    else if ( effectiveness == .5 )
        cout << "It's not very effective." << endl;
    else if ( effectiveness == 2 )
        cout << "It's super effective!" << endl;

    //pause if message is displayed
    if(effectiveness != 1 )
        this_thread::sleep_for( chrono::seconds( 1 ) );

    //determine if hit is critical
    if ( hit < 5 )
        critical = 1.5;

    //set used defense and attack stats based on physical or special move
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

    //calculate damage using all previous variables
    damage = int( ( ( ( ( ( ( static_cast<double>( 2 ) * 
        getLevel( ) ) / 5 ) + 2 ) * move.power
        * Att / Def ) / 50 ) + 2 ) * randRoll * critical * effectiveness );

    //if more damage is done to opponent than the opponent has reset damage
    if ( damage > opponent.currentHealth )
        damage = opponent.currentHealth;

    //take opponent's health based on calculated damage
    opponent.currentHealth -= damage;

    //print how much damage the attacker did
    cout << oppName << " took " << damage << " damage." << endl << endl;
    this_thread::sleep_for( chrono::seconds( 1 ) );

    //return true for hit
    return true;
}



/** ***************************************************************************
* @author Gabe Jerome
*
* @par Description
* This is the run away function. A beast can only run from a wild battle. If
* the beast that is trying to run is faster than its opponent, it will
* successfully run every time. If the running beast is slower, then its odds of
* success are calculate using each beast's speed and the number of times that
* the beast has attempted to run.
*
* @param[in, out] opponent The opposing beast.
*
* @returns True if the run attempt is successful. Else, false.
*
* @par Example
* @verbatim
    trainer player;
    int option;

    cin >> option;

    if ( option == 2 )
       {
           //if run away succeeds, exit battle
           if ( player.party[player.currBeast].runAway( player.currOpponent ) )
           {
               player.inWildBattle = false;
               return;
           }
           //if run away fails, enemy attacks and move to next turn
           else
               enemyAttack( player );
       }
* @endverbatim
******************************************************************************/
inline bool beast::runAway( beast &opponent )
{
    int odds, run;
    random_device rand;
    static int attemptNum = 1;
    int mySpeed = getSpeed( );
    int oppSpeed = opponent.getSpeed( );

    //run is always successful if runner's speed is greater than opponent
    if ( mySpeed >= oppSpeed )
    {
        attemptNum = 1;
        cout << "Got away!" << endl;
        return true;
    }

    //determine odds of success using each beast's speed and the attempt number
    odds = ( ( ( mySpeed * 32 ) / ( ( oppSpeed / 4 ) % 256 ) ) + 30 *
        attemptNum );

    //generate a random number for run
    run = rand( ) % 256;

    //if odds is greater than 255, always succeed
    //if odds is greater than random run value, success - return true
    if ( odds > 255 || run < odds )
    {
        attemptNum = 1;
        cout << "Got away!" << endl;
        return true;
    }

    //upon failure, increase static variable attempt number
    attemptNum++;

    //print failure message
    cout << "Didn't escape!" << endl;
    return false;
}



inline void beast::evolve( )
{
    int i;
    beast newBeast;

    //set ID to next beast
    base.ID++;

    //exit function if getData fails
    if ( !getData( newBeast, base.ID ) )
        return;

    //change all the base stats to the new beast
    changeBaseStats( newBeast );

    //print evolve message
    cout << nickName << " evoloved into " << base.name << '!' << endl;
    this_thread::sleep_for( chrono::seconds( 1 ) );

    //if the beast has no nickname, change it to the new beast's name
    if ( nickName != base.name )
    {
        for ( i = 0; i < 16; i++ )
            nickName[i] = base.name[i];
    }

    //print the change in stats after evolution
    printLvlUpStats( );
}



inline void beast::changeBaseStats( beast &newBeast )
{
    int i;

    //copy beast's base name
    for ( i = 0; i < 16; i++ )
        base.name[i] = newBeast.base.name[i];

    //change all of the base stats to the new beast's stats
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
    int i;
     
    //set ID
    base.ID = newBeast.base.ID;

    //change name
    for ( i = 0; i < 16; i++ )
        base.name[i] = newBeast.base.name[i];

    //set all base stats
    changeBaseStats( newBeast );

    //copy move set
    for ( i = 0; i < 30; i++ )
        base.moveSet[i] = newBeast.base.moveSet[i];

    //set experience
    experience = newBeast.experience;
    
    //change current stats
    for ( i = 0; i < 6; i++ )
        currentStats[i] = newBeast.currentStats[i];

    //change learnSet
    for ( i = 0; i < 30; i++ )
        learnSet[i] = newBeast.learnSet[i];

    //change nickname
    for ( i = 0; i < 16; i++ )
        nickName[i] = newBeast.nickName[i];

    //copy learned moves
    for ( i = 0; i < 4; i++ )
        move[i] = newBeast.move[i]; 

    //copy health
    currentHealth = newBeast.currentHealth;
}



inline void beast::learnMoves( )
{
    int i;
    int lastLearned = 0;

    for ( i = 0; i < 30; i++ )
    {
        //if the move has been learned or there are no more moves
        if ( learnSet[i].moveLevel > getLevel( ) || learnSet[i].move.type == -1 )
            return;

        //insert move into next learn spot
        changeMove( lastLearned, learnSet[i].move );

        //recalculate next learn spot
        lastLearned = ( lastLearned + 1 ) % 4;

        //set learned bool to true
        learnSet[i].learned = true;
    }
}



inline void beast::levelUp( )
{
    int i;
    int option = -1;
    int level = getLevel();

    cout << endl;

    //for i in range of max number of potential moves
    for ( i = 0; i < 30; i++ )
    {
        //if move is in the spot, the beast is high enough level, and the beast
        //is high a enough level
        if ( learnSet[i].moveLevel != 0 && learnSet[i].moveLevel <= level && 
            learnSet[i].learned == false )
        {
            //prompt user with new move message and ask what move to replace
            cout << nickName << " can learn " << learnSet[i].move.name
                << "! What move do you want to replace?" << endl;

            //print learned moves
            printMoves( );

            //option to not learn move and exit
            cout << "5: Don't learn move" << endl;

            //get input from user and check for validity
            while ( option < 1 || option > 5 )
            {
                cin >> option;
                if ( option < 1 || option > 4 )
                    cout << "Invalid input. Choose a move 1 - 5" << endl;
            }

            //exit if user prompted
            if ( option == 5 )
            {
                cout << learnSet[i].move.name << " was not learned." << endl;
                return;
            }

            //replace selected move
            changeMove( option - 1, learnSet[i].move );

            //print success message and the beast's move set
            cout << endl << nickName << " has learned " << learnSet[i].move.name << '!' << endl;
            printMoves( );

            //set learned variable to true
            learnSet[i].learned = true;
        }
    }
}



inline void beast::changeMove( int moveNum, Move replaceWith )
{
    move[moveNum] = replaceWith;
}



inline void beast::changeName( string newName )
{
    int i;
    for ( i = 0; i < 16; i++ )
        nickName[i] = '\0';

    for ( i = 0; i < 16 && i < newName.size( ); i++ )
        nickName[i] = newName[i];

    while ( i < 16 )
    {
        nickName[i] = '\0';
        i++;
    }
}



inline void beast::gainExp( beast &opponent, int yield )
{
    int expYieldRange = 80;
    random_device rand;
    int level = getLevel( );
    int oppLevel = opponent.getLevel( );
    int expYield = ( 10 * ( getBaseStatTotal( ) - 200 ) ) / int( sqrt( getBaseStatTotal( ) ) / 3 );
    int totalYield;


    totalYield = ( ( ( expYield * oppLevel ) / 6 ) *
        ( ( 2 * oppLevel + 10 ) / exp( ( oppLevel + getLevel( ) + 10 ) ), 2 ) ) * yield;

    experience += totalYield;

    cout << this->nickName << " gained " << totalYield << " experience." << endl;
    this_thread::sleep_for( chrono::seconds( 1 ) );

    if ( getLevel( ) > level )
    {
        cout << nickName << " is now level " << getLevel( ) << '!' << endl;
        this_thread::sleep_for( chrono::seconds( 1 ) );

        if ( getLevel() >= base.evolveLevel )
            evolve( );
        else
            printLvlUpStats( );

        this_thread::sleep_for( chrono::seconds( 2 ) );

        levelUp( );

        this_thread::sleep_for( chrono::seconds( 2 ) );
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
        if ( move[i].element != -1 )
            cout << "Move " << i + 1 << ": " << move[i].name << " | " <<
            eleType[move[i].element] << endl;
        else 
            cout << "Move " << i + 1 << ": empty" << endl;

    }
}



inline void beast::printOverview( )
{
    int lowExpBound;
    int highExpBound;

    lowExpBound = lvlProgression[getLevel( ) - 1];
    if ( getLevel( ) < 100 )
        highExpBound = lvlProgression[getLevel( )];

    cout << nickName << " | Lvl: " << getLevel( ) << " | Type: " << getType( ) <<
        " | HP: " << currentHealth << '/' << getMaxHP( ) << " | Exp: ";

    if ( getLevel( ) == 100 )
        cout << "MAX" << endl;
    else
        cout << getExp( ) - lowExpBound << "/" << highExpBound - lowExpBound << endl;
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
            if ( i == base.eleType2 )
                return type1 + '/' + element[i];
        }
    }

    return "ERROR";
}

inline int beast::getBaseStatTotal( )
{
    return base.health + base.defense + base.spdefense + base.attack +
        base.spattack + base.speed;
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
