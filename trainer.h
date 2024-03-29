/** ***************************************************************************
* @file
*
* @brief Trainer class
** ****************************************************************************/
#pragma once
#include "elebeastClass.h"

using namespace std;

class trainer;

void healthBar( beast curr );

void printLine( );

int find( int arr[], int tgt, int n );

bool checkLoss( trainer &player );

void giveNickname( beast &playerBeast );

void enemyAttack( trainer &player );

enum healer { small, medium, large };
enum ball { decent = 1, good, great };


#ifndef __TRAINER_H__
#define __TRAINER_H__

/**
* @brief Holds data for the player's inventory
*/
struct Bag
{
    int heals[3][20] = { 0 };   /**< The player's heals. A player can have up to
                                    20 of each of 3 different kinds of heals.*/
    int balls[3][30] = { 0 };   /**< The player's balls. A player can have up to
                                    30 of each of 3 different kinds of balls.*/
};



/**
* @brief Trainer class that holds data and functions for a beast master
*/
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
    bool inWildBattle;
    
    bool enterBag( );
    void swapParty( int beast1, int beast2 );
    bool heal( int partyNum, int healer );
    bool captureBeast( int ball );
    bool fight( );
    void setCurrBeast( );
    void putInParty( beast &newBeast );
    void printParty( );
    int getNumBeasts( );
    friend bool enterHeals( trainer &player );
    friend int enterBalls( trainer &player );
    int giveHeals( int healer, int numHeals );
    int giveBalls( int ballType, int numBalls );
    void displayFaintedBeastSwap( );
    int getAvgBeastLvl( );

private:
    
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
    money = 600;
    inWildBattle = false;
}



inline trainer::~trainer( )
{

}



inline bool trainer::enterBag( )
{
    int option;
    int totalBalls = 0;
    int catchResult;
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
            return false;

        if ( option == 1 )
            redo = enterHeals( *this );

        if ( option == 2 )
        {
            catchResult = enterBalls( *this );

            //catch attempt succeeded
            if ( catchResult == 1 )
                return true;

            //catch attempt failed
            else if ( catchResult == 2 )
                return false;

            //else no catch attempt, loop again
        }
    }

    return true;
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
    bool valid = false;
    int locationInBag;

    //make sure function call is valid
    if ( ball < 0 || ball > 2 )
    {
        cout << "There was an issue with captureBeast function call." << endl;
        return false;
    }

    cout << endl;

    //set catch rate for better balls
    if ( ball == 1 )
        ballCatchRate = 1.5;
    else if ( ball == 2 )
        ballCatchRate = 2;

    //remove ball from inventory
    locationInBag = find( bag.balls[ball], 1, 30 );
    if ( locationInBag < 0 || locationInBag > 29 )
    {
        cout << "You don't have any of those!" << endl;
        return false;
    }
    bag.balls[ball][locationInBag] = 0;

    //calculate the catch rate
    finalCatchRate = int( ( 3 * newBeast.getMaxHP( ) - 2 * newBeast.currentHealth )
        * ( catchRate * ballCatchRate ) ) / ( 3 * newBeast.getMaxHP( ) );

    //get the success rate for each shake
    shakeProb = int( 1048560 / ( sqrt( sqrt( 16711680 / finalCatchRate ) ) ) );

    //shake three time and check if each passed
    for ( i = 1; i < 4; i++ )
    {
        this_thread::sleep_for( chrono::seconds( 1 ) );

        //if a shake fails, return (not caught)
        if ( ( shakeCheck( ) % 65536 ) >= shakeProb )
        {
            cout << "The wild " << newBeast.base.name << " broke free!" << endl;
            return false;
        }

        cout << i << endl;
    }

    this_thread::sleep_for( chrono::seconds( 1 ) );

    //caught
    cout << newBeast.base.name << " was captured!" << endl;

    //put it in party
    putInParty( newBeast );
    
    cout << endl;

    return true;
}



inline bool trainer::fight( )
{
    random_device rand;
    int randMove = rand( ) % 4;
    int valid = false;
    int input;
    bool hit;

    printLine( );
    cout << endl;

    healthBar( currOpponent );
    cout << endl;
    healthBar( party[currBeast] );

    while ( !valid )
    {
        cout << endl << "Choose a move" << endl;

        party[currBeast].printMoves( );
        cout << "5: Back" << endl;

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

    if ( party[currBeast].getSpeed( ) < currOpponent.getSpeed( ) )
    {
        enemyAttack( *this );

        if ( checkLoss( *this ) )
            return false;
        else if ( party[currBeast].currentHealth == 0 )
            displayFaintedBeastSwap( );
        else
            return party[currBeast].attack( party[currBeast].move[input - 1], currOpponent );
    }
    else
    {
        hit = party[currBeast].attack( party[currBeast].move[input - 1], currOpponent );

        if ( currOpponent.currentHealth != 0 )
            enemyAttack( *this );

        return hit;
    }

    cout << endl << endl;

    return false;
}



inline void trainer::setCurrBeast( )
{
    int i;

    for ( i = 0; i < 5; i++ )
    {
        if ( party[i].base.ID != -1 && party[i].currentHealth != 0 )
        {
            currBeast = i;
            return;
        }
    }
}



inline void trainer::putInParty( beast &newBeast )
{
    int partySlot = -1;
    bool valid = false;
    int option;

    while ( !valid )
    {
        cout << "Would you like to give " << newBeast.base.name << " a nickname?" << endl;
        cout << "1: Yes\n2: No" << endl;

        cin >> option;

        if ( option == 1 )
        {
            giveNickname( newBeast );
            valid = true;
        }
        else if ( option == 2 )
            valid = true;
        else
            cout << "Please choose 1 or 2" << endl;
    }

    while ( (partySlot < 1 || partySlot > 5) )
    {
        cout << "What empty party slot would you like to put " << newBeast.nickName << " in?" << endl;
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
    int lowExpBound, highExpBound;
    for ( i = 0; i < 5; i++ )
    {
        if ( party[i].base.ID != -1 )
        {
            lowExpBound = party[i].lvlProgression[party[i].getLevel( ) - 1];
            if( party[i].getLevel() < 100 )
                highExpBound = party[i].lvlProgression[party[i].getLevel( )];

            cout << setw( 5 ) << i + 1 << ": " << party[i].nickName << " | Lvl: " << party[i].getLevel( ) << " | Type: " << party[i].getType( ) <<
                " | HP: " << party[i].currentHealth << '/' << party[i].getMaxHP( ) << " | Exp: ";

            if ( party[i].getLevel( ) == 100 )
                cout << "MAX" << endl;
            else
                cout  << party[i].getExp() - lowExpBound << "/" << highExpBound - lowExpBound << endl;
        }
        else
            cout << setw(5) << i + 1 << ": empty" << endl;
    }
}



inline int trainer::getNumBeasts( )
{
    int i, numBeasts = 0;

    for ( i = 0; i < 5; i++ )
    {
        if ( party[i].base.ID != -1 && party[i].currentHealth > 0 )
            numBeasts++;
    }

    return numBeasts;
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
        if ( location == -1 )
            return i;
        bag.heals[healer][location] = 1;
    }

    return i;
}



inline int trainer::giveBalls( int ballType, int numBalls )
{
    int location = find( bag.balls[ballType], 0, 30 );
    int i;

    if ( location == -1 )
        return 0;

    for ( i = 0; i < numBalls; i++ )
    {
        location = find( bag.balls[ballType], 0, 30 );
        if ( location == -1 )
            return i;
        bag.balls[ballType][location] = 1;
    }

    return i;
}



inline void trainer::displayFaintedBeastSwap( )
{
    int option = -1;
    bool valid = false;

    cout << party[currBeast].nickName << " fainted. Choose a beast to swap to." << endl;

    printParty( );

    while ( !valid )
    {
        cin >> option;

        if ( option < 1 || option > 5 )
            cout << "Invalid option. Please choose 1 - 6" << endl;
        else if ( party[option - 1].base.ID == -1 )
            cout << "There is no beast there! Choose a beast." << endl;
        else if ( currBeast == option - 1 )
            cout << "You are already using that beast!" << endl;
        else if ( party[option - 1].currentHealth == 0 )
            cout << "That beast is fainted." << endl;
        else
            valid = true;
    }

    currBeast = option - 1;

    cout << "Swapped to " << party[currBeast].nickName << '!' << endl;
}



inline int trainer::getAvgBeastLvl( )
{
    int i;
    int sum = 0;
    int numBeasts = 0;

    for ( i = 0; i < 5; i++ )
    {
        if ( party[i].base.ID != -1 )
        {
            sum += party[i].getLevel( );
            numBeasts++;
        }
    }

    return int( sum / numBeasts );
}



