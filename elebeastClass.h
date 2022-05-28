#include <string>

using namespace std;

#ifndef __ELEBEAST_H
#define __ELEBEAST_H

class beast
{
private:
    struct Move
    {
        string type;
        string element;
        int accuracy;
        int power;
    };

    int level;
    int exp;
    int maxHealth;
    int health;
    int defense;
    int spdefense;
    int attack;
    int spattack;
    int speed;
    string eleType;
    Move move1, move2, move3, move4;

public:
    beast( string& type );
    ~beast( );
    bool fight( Move move, beast& opponent );
    bool run( );
    void heal( string healer );
    void levelup( );
    void fireLevelUp( int level );
    void waterLevelUp( int level );
    void grassLevelUp( int level );
};

#endif


beast::beast( string& type )
{
    level = 1;
    exp = 0;
    maxHealth = 10;
    health = 10;
    defense = 1;
    spdefense = 1;
    attack = 1;
    spattack = 1;
    speed = 1;
    eleType = type;
}


beast::~beast( )
{

}


bool beast::fight(Move move, beast& opponent)
{

}


void beast::heal( string healer )
{
    if (healer == "small")
        health += 15;
    else if (healer == "medium")
        health += 25;
    else if(healer == "large")
        health += 40;
}


