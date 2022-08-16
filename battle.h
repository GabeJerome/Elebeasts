#pragma once
#include "trainer.h"

using namespace std;

void generateRandBeast( trainer player, beast &randBeast, bool boss = false );

void findEvolution( beast &randBeast );

void getRandName( trainer &player );

#ifndef __BATTLE_H__
#define __BATTLE_H__

class battle
{
public:
    battle( );
    ~battle( );
    bool wildBattle( trainer &player );
    bool trainerBattle( trainer &player, bool boss = false );
    void displayBattleMenu( trainer &player );
    bool displayCurrBeastSwap( trainer &player );

private:

};
#endif



inline battle::battle( )
{

}



inline battle::~battle( )
{

}



inline bool battle::wildBattle( trainer &player )
{
    random_device oppMove;
    beast randBeast, nullBeast;
    bool won;
    int prizeMoney;

    generateRandBeast( player, randBeast );

    player.inWildBattle = true;

    player.currOpponent = randBeast;

    while ( !checkLoss( player ) && player.currOpponent.currentHealth != 0 )
    {
        printLine( );
        cout << endl;
        displayBattleMenu( player );
        if ( !player.inWildBattle )
            return false;
    }

    won = !checkLoss( player );

    if ( won )
    {
        cout << player.currOpponent.nickName << " was defeated! Good job!" << endl;
        player.party[player.currBeast].gainExp( player.currOpponent );
        prizeMoney = ( 20 * player.getAvgBeastLvl( ) );
        cout << "You got " << prizeMoney << " coins for winning." << endl;
        player.money += prizeMoney;
    }
    else
    {
        prizeMoney = ( 20 * player.getAvgBeastLvl( ) );
        if ( prizeMoney > player.money )
            prizeMoney = player.money;
        cout << "You lost to " << player.currOpponent.nickName << '.' << endl;
        cout << "You dropped " << prizeMoney << " coins while fleeing." << endl;
        player.money -= prizeMoney;
    }

    player.setCurrBeast( );
    player.currOpponent = nullBeast;

    player.inWildBattle = false;

    return won;
}



inline bool battle::trainerBattle( trainer &player, bool boss )
{
    trainer opponent;
    int currOpponentBeast = 0;
    int i, numBeasts;
    beast randBeast;
    string oppName;
    int prizeMoney, moneyMultiplier = 1;
    
    getRandName( opponent );

    numBeasts = player.getNumBeasts( );

    oppName = opponent.name;

    if ( boss )
    {
        //boss get another beast if not already maxed
        if ( numBeasts < 5 )
            numBeasts++;

        //add boss title to opponent
        oppName = "Boss " + oppName;

        //double the prize money for boss
        moneyMultiplier = 2;
    }

    //generate random beasts for opponent
    for ( i = 0; i < numBeasts; i++ )
    {
        generateRandBeast( player, randBeast );
        opponent.party[i] = randBeast;
    }
    
    //set player's current oppent
    player.currOpponent = opponent.party[0];
    
    //infinite loop until battle is complete
    while ( true )
    {
        //set opponent's current beast
        opponent.party[currOpponentBeast] = player.currOpponent;

        //loss
        if ( checkLoss( player ) )
        {
            cout << "You lost to " << oppName << "." << endl;
            prizeMoney = ( 100 * player.getAvgBeastLvl( ) );
            if ( prizeMoney > player.money )
                prizeMoney = player.money;
            cout << "You gave " << oppName << " " << prizeMoney << " coins." << endl;
            return false;
        }
        //win
        if ( checkLoss( opponent ) )
        {
            cout << "You beat " << oppName << "." << endl;
            prizeMoney = ( 100 * opponent.getAvgBeastLvl( ) ) * moneyMultiplier;
            cout << oppName << " gave you " << prizeMoney << " coins." << endl;
            return true;
        }

        if ( opponent.party[currOpponentBeast].currentHealth <= 0 )
        {
            //display opponent fainted message to player
            this_thread::sleep_for( chrono::seconds( 1 ) );
            cout << player.currOpponent.nickName << " fainted." << endl;
            this_thread::sleep_for( chrono::seconds( 1 ) );

            //gain exp
            player.party[player.currBeast].gainExp( player.currOpponent );

            //move to next opponent beast
            currOpponentBeast++;
            player.currOpponent = opponent.party[currOpponentBeast];
            cout << opponent.name << " sent out " << opponent.party[currOpponentBeast].nickName << "." << endl;
            this_thread::sleep_for( chrono::seconds( 1 ) );
        }

        //swap fainted beast
        if ( player.party[player.currBeast].currentHealth == 0 )
            player.displayFaintedBeastSwap( );


        printLine( );
        cout << endl << oppName << "  ";

        //display how many beasts opponent has
        for ( i = 0; i < 5; i++ )
        {
            cout << char( 179 );
            if ( i < opponent.getNumBeasts( ) )
                cout << char( 219 );
            else
                cout << char( 176 );
        }
        cout << char(179) << endl;
        
        //battle menu
        displayBattleMenu( player );
    }

    return false;
}



inline void battle::displayBattleMenu( trainer &player )
{
    int option = -1;
    bool valid = false;
    random_device rand;
    int randMove = rand( ) % 4;

    while ( !valid )
    {
        healthBar( player.currOpponent );
        cout << endl;
        healthBar( player.party[player.currBeast] );

        cout << endl << "Choose an action" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Run" << endl;
        cout << "3. Bag" << endl;
        cout << "4. Party" << endl;

        cin >> option;

        if ( option < 1 || option > 4 )
            cout << "Invalid option. Please choose 1 - 4." << endl;
        else if ( option == 2 && !player.inWildBattle )
        {
            cout << "You can't run from trainer battles!" << endl;
            this_thread::sleep_for( chrono::seconds( 1 ) );
        }
        else
            valid = true;

        cout << endl;

        if ( option == 1 )
            player.fight( );
        else if ( option == 2 )
        {
            if ( player.party[player.currBeast].runAway( player.currOpponent ) )
            {
                player.inWildBattle = false;
                return;
            }
            else
            {
                while ( player.currOpponent.move[randMove].type == -1 )
                    randMove = rand( ) % 4;

                player.currOpponent.attack( player.currOpponent.move[randMove], player.party[player.currBeast], true );
            }
        }
        else if ( option == 3 )
            valid = player.enterBag( );
        else if ( option == 4 )
            valid = displayCurrBeastSwap( player );
    }
}



inline bool battle::displayCurrBeastSwap( trainer &player )
{
    int option = -1;
    bool valid = false;
    random_device rand;
    int randMove = rand( ) % 4;

    cout << "Choose a beast to swap." << endl;

    player.printParty( );
    cout << "6: Back" << endl;

    while ( !valid )
    {
        cin >> option;

        if ( option == 6 )
            return false;

        if ( option < 1 || option > 5 )
            cout << "Invalid option. Please choose 1 - 6" << endl;
        else if ( player.party[option - 1].base.ID == -1 )
            cout << "There is no beast there! Choose a beast." << endl;
        else if ( player.currBeast == option - 1 )
            cout << "You are already using that beast!" << endl;
        else if ( player.party[option - 1].currentHealth == 0 )
            cout << "That beast is fainted." << endl;
        else
            valid = true;
    }

    player.currBeast = option - 1;

    cout << "Swapped to " << player.party[player.currBeast].nickName << '!' << endl << endl;

    while ( player.currOpponent.move[randMove].type == -1 )
        randMove = rand( ) % 4;

    player.currOpponent.attack( player.currOpponent.move[randMove], player.party[player.currBeast] );

    return true;
}