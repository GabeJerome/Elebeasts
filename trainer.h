#include "elebeastClass.h"
#include <thread>

using namespace std;

enum healer { small, medium, large };
enum ball { decent = 1, good, great };


#ifndef __TRAINER_H__
#define __TRAINER_H__

struct Bag
{
    int heals[20] = { 0 };
    int balls[100] = { 0 };
};

class trainer
{
public:
    trainer( );
    ~trainer( );

    char name[16] = "Julio";
    Bag bag;
    beast party[5];
    int currBeast;
    
    void swapParty( int beast1, int beast2 );
    void heal( int healer );
    bool captureBeast( beast &newBeast, int ball );
    void putInParty( beast &newBeast );
    void printParty( );
    //add beast storage box?
    //add achievments?

private:

};

#endif



inline trainer::trainer( )
{
    int i;
    beast null;
    
    for ( i = 0; i < 5; i++ )
        party[i] = null;

    currBeast = 0;
}



inline trainer::~trainer( )
{

}



inline void trainer::swapParty( int beast1, int beast2 )
{
    beast temp = party[beast1];
    party[beast1] = party[beast2];
    party[beast2] = temp;
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



inline bool trainer::captureBeast( beast &newBeast, int ball )
{
    random_device shakeCheck;
    int i;
    int finalCatchRate;
    unsigned int shakeProb;
    int catchRate = int(( 6000 / cbrt( newBeast.getBaseStatTotal( ) ) ) - 700);
    float ballCatchRate = 1;

    if ( ball == 2 )
        ballCatchRate = 1.5;
    else if ( ball == 3 )
        ballCatchRate = 2;

    finalCatchRate = int( ( 3 * newBeast.getMaxHP( ) - 2 * newBeast.currentHealth )
        * ( catchRate * ballCatchRate ) ) / ( 3 * newBeast.getMaxHP( ) );

    shakeProb = int( 1048560 / ( sqrt( sqrt( 16711680 / finalCatchRate ) ) ) );

    for ( i = 1; i < 4; i++ )
    {
        this_thread::sleep_for( chrono::seconds( 1 ) );
        if ( ( shakeCheck( ) % 65536 ) >= shakeProb )
        {
            cout << "The wild " << newBeast.base.name << " broke free!" << endl;
            return false;
        }

        cout << i << endl;
    }

    this_thread::sleep_for( chrono::seconds( 1 ) );
    cout << newBeast.base.name << " was captured!" << endl;

    putInParty( newBeast );
    

    return true;
}



inline void trainer::putInParty( beast &newBeast )
{
    int partySlot = -1;

    while ( (partySlot < 1 || partySlot > 5) )
    {
        cout << "What empty party slot would you like to put " << newBeast.base.name << " in?" << endl;
        printParty( );

        cin >> partySlot;

        if ( partySlot < 1 || partySlot > 5 )
            cout << "That is not a valid slot. Enter a number 1 - 5." << endl;
        else if ( party[partySlot - 1].base.ID != -1 )
        {
            cout << "That is not an empty slot! Pick an empty slot." << endl;
            partySlot = -1;
        }
    }

    party[partySlot - 1] = newBeast;

    cout << newBeast.base.name << " is now in slot " << partySlot << '.' << endl;
    printParty( );
}



inline void trainer::printParty( )
{
    int i;

    for ( i = 0; i < 5; i++ )
    {
        if ( party[i].base.ID != -1 )
            cout << i + 1 << ": " << party[i].nickName << ' ' << party[i].getType( ) << endl;
        else
            cout << i + 1 << ": empty" << endl;
    }
}
