#include <string>
#include <iostream>
#include <random>
#include "moves.h"

using namespace std;

#ifndef __ELEBEAST_H__
#define __ELEBEAST_H__

class beast
{
private:
    int level;
    int experience;
    int baseHealth;
    int currentHealth;
    int baseDefense, currDef;
    int baseSpdefense, currSpDef;
    int baseAttack, currAtt;
    int baseSpattack, currSpAtt;
    int baseSpeed, currSpeed;
    int eleType;

public:
    beast( );
    beast(int lvl, int exp, int maxHlth, int currHlth, int def,
        int spdef, int att, int spatt, int spd, int type);
    ~beast( );
    bool fight( Move move, beast& opponent );
    bool runAway( beast& opponent);
    void heal( string healer );
    void levelup( );
    void levelUp();
    void changeMove(int move, Move replaceWith);
    Move move[4];
};

#endif



inline beast::beast( )
{
    level = 0;
    experience = 0;
    baseHealth = 0;
    currentHealth = baseHealth;
    baseDefense = 0;
    baseSpdefense = 0;
    baseAttack = 0;
    baseSpattack = 0;
    baseSpeed = 0;
    eleType = 0;
}

inline beast::beast(int lvl, int exp, int maxHlth, int currHlth, int def,
    int spdef, int att, int spatt, int spd, int type)
{
    level = lvl;
    experience = exp;
    baseHealth = maxHlth;
    currentHealth = baseHealth;
    baseDefense = def;
    baseSpdefense = spdef;
    baseAttack = att;
    baseSpattack = spatt;
    baseSpeed = spd;
    eleType = type;
}


inline beast::~beast( )
{

}


inline bool beast::fight(Move move, beast& opponent)
{
    random_device rand;
    random_device roll;
    int hit = rand() % 101;

    if (hit > move.accuracy)
        return false;

    double randRoll = (double(roll() % 16) / 100) + .85;
    int damage;
    int Def, Att;
    double critical = 1;
    double effectiveness;
    double effectiveChart[18][18] = 
    {              /* 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17*/
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


    //TODO: add comments
    

    if (hit < 5)
        critical = 1.5;

    if (move.type == 0)
    {
        Def = opponent.baseSpdefense;
        Att = baseSpattack;
    }
    else
    {
        Def = opponent.baseDefense;
        Att = baseAttack;
    }

    damage = int(((((((static_cast<double>(2) * level) / 5) + 2) * move.power
        * Att / Def) / 50) + 2) * randRoll * critical * effectiveness);

    opponent.currentHealth -= damage;

    if (opponent.currentHealth < 0)
        opponent.currentHealth = 0;

    return true;
}



inline bool beast::runAway(beast& opponent)
{
    int odds, run;
    random_device rand;

    odds = (((baseSpeed * 32) / ((opponent.baseSpeed / 4) % 256)) + 30 /*multiply by number of run attempts*/);
    
    run = rand() % 256;

    if (odds > 255 || run < odds)
        return true;

    return false;
}



inline void beast::heal( string healer )
{
    if (currentHealth == 0)
    {
        cout << "This beast needs to be revived first!" << endl;
        return;
    }

    if (healer == "small")
        currentHealth += 15;
    else if (healer == "medium")
        currentHealth += 25;
    else if(healer == "large")
        currentHealth += 40;

    if (currentHealth > baseHealth)
        currentHealth = baseHealth;
}



inline void beast::changeMove(int moveNum, Move replaceWith)
{
    move[moveNum] = replaceWith;
}



//TODO: test runAway function, create more beasts and moves.