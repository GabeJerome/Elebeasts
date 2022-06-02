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
    Move move[4];    //TODO: fill moves

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
};



inline beast::beast( int type )
{
    int i;

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
    int effectiveness = 1;

    //TODO: calculate effectiveness
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