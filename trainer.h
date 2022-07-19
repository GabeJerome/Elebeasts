#include "elebeastClass.h"
#include <thread>

using namespace std;



void healthBar( beast curr );

int find( int arr[], int tgt, int n );

enum healer { small, medium, large };
enum ball { decent = 1, good, great };


#ifndef __TRAINER_H__
#define __TRAINER_H__

struct Bag
{
    int heals[3][20] = { 0 };
    int balls[3][30] = { 0 };
};

class trainer
{
public:
    trainer( );
    ~trainer( );

    char name[16] = "Trainer";
    Bag bag;
    beast party[5];
    int currBeast;
    int money;
    beast currOpponent;
    
    void enterBag( );
    void swapParty( int beast1, int beast2 );
    bool heal( int partyNum, int healer );
    bool captureBeast( int ball );
    bool fight( );
    void putInParty( beast &newBeast );
    void printParty( );
    friend bool enterHeals( trainer &me );
    friend bool enterBalls( trainer &me );
    int giveHeals( int healer, int numHeals );
    int giveBalls( int ballType, int numBalls );
    void displayBattleMenu( );
    //add beast storage box?
    //add achievments?
};

#endif



inline trainer::trainer( )
{
    int i;
    beast null;
    
    for ( i = 0; i < 5; i++ )
        party[i] = null;

    currBeast = 0;
    money = 0;
}



inline trainer::~trainer( )
{

}



inline void trainer::enterBag( )
{
    int option;
    int totalBalls = 0;
    bool redo = false;
    

    while ( !redo )
    {
        option = -1;

        cout << "What would you like to use?" << endl;
        cout << "1: Heals" << endl;
        cout << "2: Balls" << endl;
        cout << "3: Exit" << endl;

        while ( option < 1 || option > 3 )
        {
            cin >> option;

            if ( option < 1 || option > 3 )
                cout << "Invalid option. Please choose 1 - 3." << endl;
        }

        if ( option == 3 )
            return;

        if ( option == 1 )
            redo = enterHeals( *this );

        if ( option == 2 )
            redo = enterBalls( *this );
    }
}



inline void trainer::swapParty( int beast1, int beast2 )
{
    beast temp = party[beast1];
    party[beast1] = party[beast2];
    party[beast2] = temp;
}



inline bool trainer::heal(int partyNum, int healer )
{
    if ( party[partyNum].currentHealth == 0 )
    {
        cout << "This beast needs to be revived first!" << endl;
        return false;
    }

    if ( healer == 0 )
        party[partyNum].currentHealth += 15;
    else if ( healer == 1 )
        party[partyNum].currentHealth += 50;
    else if ( healer == 2 )
        party[partyNum].currentHealth += 100;

    if ( party[partyNum].currentHealth > party[partyNum].getMaxHP( ) )
        party[partyNum].currentHealth = party[partyNum].getMaxHP( );

    bag.heals[healer][find( bag.heals[healer], 1, 20 )] = 0;

    return true;
}



inline bool trainer::captureBeast( int ball )
{
    random_device shakeCheck;
    beast newBeast = currOpponent;
    int i;
    int finalCatchRate;
    unsigned int shakeProb;
    int catchRate = int(( 6000 / cbrt( newBeast.getBaseStatTotal( ) ) ) - 700);
    float ballCatchRate = 1;

    cout << endl;

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
    
    cout << endl;

    return true;
}



inline bool trainer::fight( )
{
    int valid = false;
    int input;

    cout << "Choose a move" << endl;

    party[currBeast].printMoves( );
    cout << "5: Back" << endl;

    while ( !valid )
    {
        cin >> input;

        if ( input == 5 )
            return false;

        if ( input < 1 || input > 4 )
            cout << "Invalid option. Please choose 1 - 5." << endl;
        else if ( party[currBeast].move[input - 1].element == -1 )
            cout << "There is no move there. Please choose a move." << endl;
        else
            valid = true;
    }

    cout << endl;

    if( party[currBeast].attack( party[currBeast].move[input - 1], currOpponent ) )
        return true;

    cout << endl;

    return false;
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
            cout << i + 1 << ": " << party[i].nickName << " | Type: " << party[i].getType( ) <<
            " | HP: " << party[i].currentHealth << '/' << party[i].getMaxHP( ) << endl;
        else
            cout << i + 1 << ": empty" << endl;
    }
}



inline int trainer::giveHeals( int healer, int numHeals )
{
    int location = find( bag.heals[healer], 0, 20 );
    int i;

    if ( location == -1 )
        return 0;

    for ( i = 0; i < numHeals; i++ )
    {
        location = find( bag.heals[healer], 0, 20 );
        bag.heals[healer][location] = 1;
    }

    return i;
}



inline int trainer::giveBalls( int ballType, int numBalls )
{
    int location = find( bag.balls[ballType], 0, 20 );
    int i;

    if ( location == -1 )
        return 0;

    for ( i = 0; i < numBalls; i++ )
    {
        location = find( bag.balls[ballType], 0, 30 );
        bag.balls[ballType][location] = 1;
    }

    return i;
}



inline void trainer::displayBattleMenu( )
{
    healthBar( currOpponent );
    cout << endl;
    healthBar( party[currBeast] );

    //Finish alongside wildBattle function in functions.cpp
}



