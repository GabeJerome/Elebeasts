#include <string>

using namespace std;

#ifndef __ELEBEAST_H
#define __ELEBEAST_H

class beast
{
private:
    struct Move
    {
        int type;
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
    Move move1, move2, move3, move4;    //TODO: fill moves

public:
    beast( string& type );
    ~beast( );
    bool fight( Move move, beast& opponent );
    bool run( );
    void heal( string healer );
    void selectMove(int move);
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
    std::random_device rand;
    std::random_device roll;
    int hit = rand() % 101;
    float randRoll = (roll() % 101) / 100;
    int damage;
    int Def, Att;
    int critical = 1;
    int effectiveness = 1;

    //TODO: calculate effectiveness

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

    if (hit > move.accuracy)
        return false;

    damage = ((((((2 * level) / 5) + 2) * move.power * Att / Def) / 50) + 2)
        * randRoll * critical * effectiveness;

    opponent.health -= damage;

    return true;
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


void beast::selectMove(int move)
{

}