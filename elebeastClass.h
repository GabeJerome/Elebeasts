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
    int exp;
    int maxHealth;
    int health;
    int defense;
    int spdefense;
    int attack;
    int spattack;
    int speed;
    int eleType;

public:
    beast( int type );
    ~beast( );
    bool fight( Move move, beast& opponent );
    bool run( );
    void heal( string healer );
    void selectMove(int move);
    void levelup( );
    void fireLevelUp( int level );
    void waterLevelUp( int level );
    void grassLevelUp( int level );
    void changeMove(int move, Move replaceWith);
    Move move[4];
};



inline beast::beast( int type )
{
    level = 1;
    exp = 0;
    maxHealth = 10;
    health = maxHealth;
    defense = 1;
    spdefense = 1;
    attack = 1;
    spattack = 1;
    speed = 1;
    eleType = type;
}


inline beast::~beast( )
{

}


inline bool beast::fight(Move move, beast& opponent)
{
    std::random_device rand;
    std::random_device roll;
    int hit = rand() % 101;
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
    if (hit > move.accuracy)
            return false;

    if (hit < 5)
        critical = 1.5;

    if (move.type == 0)
    {
        Def = opponent.spdefense;
        Att = spattack;
    }
    else
    {
        Def = opponent.defense;
        Att = attack;
    }

    damage = int(((((((static_cast<double>(2) * level) / 5) + 2) * move.power
        * Att / Def) / 50) + 2) * randRoll * critical * effectiveness);

    opponent.health -= damage;

    return true;
}



inline void beast::heal( string healer )
{
    if (health == 0)
    {
        cout << "This beast needs to be revived first!" << endl;
        return;
    }

    if (healer == "small")
        health += 15;
    else if (healer == "medium")
        health += 25;
    else if(healer == "large")
        health += 40;

    if (health > maxHealth)
        health = maxHealth;
}



inline void beast::changeMove(int moveNum, Move replaceWith)
{
    move[moveNum] = replaceWith;
}


#endif