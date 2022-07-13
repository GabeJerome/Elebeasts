#include "elebeastClass.h"

using namespace std;

#ifndef __TRAINER_H__
#define __TRAINER_H__

struct Bag
{
    int heals[20];

};

class trainer
{
public:
    char name[16];
    Bag bag;
    beast party[5];
    int currBeast;
    
    void swapParty( int beast1, int beast2 );
    void heal( int healer );
    //add achievments?

private:

};

#endif



inline void trainer::swapParty( int beast1, int beast2 )
{
    beast temp;
}



inline void trainer::heal( int healer )
{
    if ( party[currBeast].currentHealth == 0 )
    {
        cout << "This beast needs to be revived first!" << endl;
        return;
    }

    if ( healer == 0 )
        party[currBeast].currentHealth += 15;
    else if ( healer == 1 )
        party[currBeast].currentHealth += 25;
    else if ( healer == 2 )
        party[currBeast].currentHealth += 40;

    if ( party[currBeast].currentHealth > party[currBeast].getMaxHP( ) )
        party[currBeast].currentHealth = party[currBeast].getMaxHP( );
}