#include <string>

using namespace std;

#ifndef __ELEBEAST_H
#define __ELEBEAST_H

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
    string eleType;

    struct moveSet
    {
        struct move1
        {
            string type;
            string element;
            int accuracy;
            int power;
        };
        struct move2
        {
            string type;
            string element;
            int accuracy;
            int power;
        };
        struct move3
        {
            string type;
            string element;
            int accuracy;
            int power;
        };
        struct move4
        {
            string type;
            string element;
            int accuracy;
            int power;
        };
    };

public:
    beast( string& type );
    ~beast( );
    bool combat( string move );
    bool run( );
    void heal( );
    void levelup( );
    void fireLevelUp( moveSet& moves, int level );
    void waterLevelUp( moveSet& moves, int level );
    void grassLevelUp( moveSet& moves, int level );
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