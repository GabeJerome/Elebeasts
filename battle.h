#pragma once
#include "trainer.h"

using namespace std;


#ifndef __BATTLE_H__
#define __BATTLE_H__

class battle
{
public:
    battle( );
    ~battle( );
    bool wildBattle( trainer &player, beast &opp );
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



inline bool battle::wildBattle( trainer &player, beast &opp )
{
    random_device oppMove;
    beast nullBeast;
    bool won;

    player.currOpponent = opp;

    while ( !checkLoss( player ) && player.currOpponent.currentHealth != 0 )
        displayBattleMenu( player );

    won = !checkLoss( player );

    if ( won )
    {
        cout << player.currOpponent.nickName << " was defeated! Good job!" << endl;
        player.party[player.currBeast].gainExp( player.currOpponent );
    }
    else
        cout << "You lost to " << player.currOpponent.nickName << '.';

    player.setCurrBeast( );
    player.currOpponent = nullBeast;

    return won;
}



inline void battle::displayBattleMenu( trainer &player )
{
    int option = -1;
    bool valid = false;

    while ( !valid )
    {
        printLine( );
        cout << endl;

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
        else
            valid = true;

        cout << endl;

        if ( option == 1 )
            player.fight( );
        if ( option == 2 )
            player.party[player.currBeast].runAway( player.currOpponent );
        if ( option == 3 )
            valid = player.enterBag( );
        if ( option == 4 )
            valid = displayCurrBeastSwap( player );
    }
    //Finish alongside wildBattle function in functions.cpp
}



inline bool battle::displayCurrBeastSwap( trainer &player )
{
    int option = -1;
    bool valid = false;

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

    cout << "Swapped to " << player.party[player.currBeast].nickName << '!' << endl;

    return true;
}