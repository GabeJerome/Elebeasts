/** ***************************************************************************
* @file
*
* @brief Battle class
** ****************************************************************************/
#pragma once
#include "trainer.h"

using namespace std;

void generateRandBeast( trainer player, beast &randBeast, int type = 0 );

void findEvolution( beast &randBeast );

void getRandName( trainer &player );

#ifndef __BATTLE_H__
#define __BATTLE_H__

/**
* @brief Battle class that runs all of the player's battles.
*/
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



/** ***************************************************************************
* @author Gabe Jerome
*
* @par Description
* This is the constructor for the battle class. It does not need to set any
* variable.
*
* @param[in] none
*
* @returns nothing
*
* @par Example
* @verbatim
    battle sampleBattle;
  @endverbatim
* ****************************************************************************/
inline battle::battle( )
{

}



/** ***************************************************************************
* @author Gabe Jerome
*
* @par Description
* This is the deconstructor for the battle class. There is no dynamic memory
* in this class that needs to be cleared.
*
* @param[in] none
*
* @returns nothing
*
* @par Example
* @verbatim
  int main( )
  {
      battle sampleBattle;
  }
  //The deconstructor is called when the instance goes out of scope
  @endverbatim
* ****************************************************************************/
inline battle::~battle( )
{

}



/** ***************************************************************************
* @author Gabe Jerome
*
* @par Description
* This function runs a wild battle for the player. It displays battle options
* and calls functions according to what the player selected. It ensures that
* the player gives a valid input and displays a message if the input is invalid.
* It will loop until the player is out of beasts, the wild beast is fainted,
* the wild beast is caught, or the player successfully runs away. The wild
* beast's strength is calculated according to the trainer's current beast
* (the one that they will use first).
*
* @param[in, out] player The player's trainer class.
*
* @returns True if the player beats the wild beast, if the player catches the
* wild beast, or if the player successfully runs away. False if the player
* loses.
*
* @par Example
* @verbatim
  trainer player;
  battle sampleBattle;

  sampleBattle.wildBattle( player );

  @endverbatim
* ****************************************************************************/
inline bool battle::wildBattle( trainer &player )
{
    random_device oppMove;
    beast randBeast, nullBeast;
    bool won;
    int prizeMoney;

    //set the the first, healthy beast in party to current beast
    player.setCurrBeast( );

    //get a random beast based on currBeast's level
    generateRandBeast( player, randBeast );

    //Enter wild battle
    player.inWildBattle = true;

    //set currOpponent
    player.currOpponent = randBeast;

    //begin battle loop until someone loses
    while ( !checkLoss( player ) && player.currOpponent.currentHealth != 0 )
    {
        printLine( );
        cout << endl;
        displayBattleMenu( player );

        //If the beast is captured
        if ( !player.inWildBattle )
            return true;
    }

    //set to display correct messages and return boolean value
    won = !checkLoss( player );

    //win
    if ( won )
    {
        cout << player.currOpponent.nickName << " was defeated! Good job!" << endl;
        player.party[player.currBeast].gainExp( player.currOpponent );
        prizeMoney = ( 20 * player.getAvgBeastLvl( ) );
        cout << "You got " << prizeMoney << " coins for winning." << endl;
        player.money += prizeMoney;
    }
    //loss
    else
    {
        prizeMoney = ( 20 * player.getAvgBeastLvl( ) );
        if ( prizeMoney > player.money )
            prizeMoney = player.money;
        cout << "You lost to " << player.currOpponent.nickName << '.' << endl;
        cout << "You dropped " << prizeMoney << " coins while fleeing." << endl;
        player.money -= prizeMoney;
    }

    //set the the first, healthy beast in party to current beast
    player.setCurrBeast( );

    //erase current opponent
    player.currOpponent = nullBeast;

    //exit wild battle
    player.inWildBattle = false;

    return won;
}



/** ***************************************************************************
* @author Gabe Jerome
*
* @par Description
* This function runs a trainer battle or a boss battle for the player. It ensures that
* the player gives a valid input and displays a message if the input is invalid.
* It will loop until the player or the opponent is out of beasts. It can generate
* a random trainer whose strength is derived from the average level of all the
* player's beasts. If it is a boss battle, the trainer will have a higher
* multiplier for random level generation for each beast. A boss will also have
* one more beast than the trainer if the trainer does not have five beasts.
* The boss parameter is assumed to be false.
*
* @param[in, out] player The player's trainer class.
* @param[in] boss Determines if the opponent will be a boss or a regular trainer.
*
* @returns True if the player wins. False if the player loses.
*
* @par Example
* @verbatim
  trainer player;
  battle sampleBattle;

  sampleBattle.trainerBattle( player );

  sampleBattle.trainerBattle( player, true );

  @endverbatim
* ****************************************************************************/
inline bool battle::trainerBattle( trainer &player, bool boss )
{
    trainer opponent;
    int currOpponentBeast = 0;
    int i, numBeasts;
    beast randBeast;
    string oppName;
    int prizeMoney, moneyMultiplier = 1;

    //set the the first, healthy beast in party to current beast
    player.setCurrBeast( );
    
    //get a name for the opponent
    getRandName( opponent );

    //find the number of beasts for the opponent
    numBeasts = player.getNumBeasts( );

    //give the random name to the opponent
    oppName = opponent.name;

    if ( boss )
    {
        //boss gets another beast if not already maxed
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
        if ( boss )
            generateRandBeast( player, randBeast, 2 );
        else
            generateRandBeast( player, randBeast, 1 );
        opponent.party[i] = randBeast;
    }
    
    //set player's current oppent
    player.currOpponent = opponent.party[0];
    
    //infinite loop until battle is complete
    while ( true )
    {
        //set opponent's current beast
        opponent.party[currOpponentBeast] = player.currOpponent;

        //if currOpponentBeast is fainted
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

        //loss
        if ( checkLoss( player ) )
        {
            cout << "You lost to " << oppName << "." << endl;
            prizeMoney = ( 100 * player.getAvgBeastLvl( ) );
            if ( prizeMoney > player.money )
                prizeMoney = player.money;
            cout << "You gave " << oppName << " " << prizeMoney << " coins." << endl;
            player.money -= prizeMoney;
            return false;
        }
        //win
        if ( checkLoss( opponent ) )
        {
            cout << "You beat " << oppName << "." << endl;
            prizeMoney = ( 100 * opponent.getAvgBeastLvl( ) ) * moneyMultiplier;
            cout << oppName << " gave you " << prizeMoney << " coins." << endl;
            player.money += prizeMoney;
            return true;
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
}



/** ***************************************************************************
* @author Gabe Jerome
*
* @par Description
* This function displays the battle menu for wild and trainer battles. It prints
* each beast's name, health bar, and level. Then, it prints the player's
* options: attack, run, bag, party. Attack calls the trainer's attack member
* function. Run will attempt a run away only in wild battles, otherwise it
* informs the player and displays the option again. Bag will enter the player's
* inventory for them to use balls or heals. Party allows the player to switch
* to a different beast.
*
* @param[in, out] player The player's trainer class.
*
* @returns void
*
* @par Example
* @verbatim
  trainer player;
  battle sampleBattle;

  sampleBattle.trainerBattle( player );
  //displayBattleMenu is only called within one of the battle functions
  //The text below is printed
            _________________________
  Fotosin: │█████████████████████████│
  lvl 13                   34/34

            _________________________
  Stropie: │█████████████████████████│
  lvl 12                   32/32

  Choose an action
  1. Attack
  2. Run
  3. Bag
  4. Party
  @endverbatim
* ****************************************************************************/
inline void battle::displayBattleMenu( trainer &player )
{
    int option = -1;
    bool valid = false;
    random_device rand;
    int randMove = rand( ) % 4;

    while ( !valid )
    {
        //print health bars
        healthBar( player.currOpponent );
        cout << endl;
        healthBar( player.party[player.currBeast] );

        //display battle options
        cout << endl << "Choose an action" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Run" << endl;
        cout << "3. Bag" << endl;
        cout << "4. Party" << endl;

        //take in option
        cin >> option;

        //make sure the option is valid
        if ( option < 1 || option > 4 )
            cout << "Invalid option. Please choose 1 - 4." << endl;
        //make sure player can only run from a trainer battle
        else if ( option == 2 && !player.inWildBattle )
        {
            cout << "You can't run from trainer battles!" << endl;
            this_thread::sleep_for( chrono::seconds( 1 ) );
        }
        else
            valid = true;

        cout << endl;

        //enter fight menu
        if ( option == 1 )
            player.fight( );

        //attempt to run away
        else if ( option == 2 )
        {
            //if run away succeeds, exit battle
            if ( player.party[player.currBeast].runAway( player.currOpponent ) )
            {
                player.inWildBattle = false;
                return;
            }
            //if run away fails, enemy attacks and move to next turn
            else
                enemyAttack( player );
        }

        //enter bag function
        else if ( option == 3 )
        {
            //enterBag returns true if the player used an item, else next turn
            if ( player.enterBag( ) )
                return;
        }

        //swap beasts function
        else if ( option == 4 )
        {
            //valid is true if a beast is swapped
            valid = displayCurrBeastSwap( player );

            //if a beast is swapped, the enemy gets to attack
            if ( valid )
                enemyAttack( player );
        }
    }
}



/** ***************************************************************************
* @author Gabe Jerome
*
* @par Description
* This function displays a current beast swap. It is called in a battle
* function, so it displays options and checks for valid user input. A user's
* input is invalid if they choose a beast that is currently being used,
* fainted, or there is no beast in the slot. Valid input will result in the
* player switching to that beast in the battle. The order of the player's party
* is unaffected outside of the battle.
*
* @param[in, out] player The player's trainer class.
*
* @returns True if the player chooses to swap a beast. False if the players
* selects "back".
*
* @par Example
* @verbatim
  trainer player;
  battle sampleBattle;

  sampleBattle.trainerBattle( player );
  //displayCurrBeastSwap is only called within one of the battle functions
  //Below is a sample of what will be printed.

  Choose a beast to swap to.
    1: Chad | Lvl: 12 | Type: grass | HP: 32/32 | Exp: 386/469
    2: Apolozard | Lvl: 17 | Type: water/fighting | HP: 47/47 | Exp: 401/919
    3: Marshall | Lvl: 14 | Type: grass | HP: 36/36 | Exp: 125/631
    4: empty
    5: empty
    6: Back
  @endverbatim
* ****************************************************************************/
inline bool battle::displayCurrBeastSwap( trainer &player )
{
    int option = -1;
    bool valid = false;

    //enter loop until a valid option is selected
    while ( !valid )
    {
        //print swap beast options
        cout << "Choose a beast to swap to." << endl;
        player.printParty( );
        cout << "    6: Back" << endl;

        //get user input
        cin >> option;

        //exit bag and return false to indicate no use of an item
        if ( option == 6 )
            return false;

        //check for a valid input
        if ( option < 1 || option > 5 )
            cout << "Invalid option. Please choose 1 - 6" << endl;

        //invalid if there is no beast in the party slot
        else if ( player.party[option - 1].base.ID == -1 )
            cout << "There is no beast there! Choose a beast." << endl;

        //invalid if beast is already out
        else if ( player.currBeast == option - 1 )
            cout << "You are already using that beast!" << endl;

        //invalid if the beast has no health
        else if ( player.party[option - 1].currentHealth == 0 )
            cout << "That beast is fainted." << endl;

        //valid
        else
            valid = true;
    }

    //set player's current beast
    player.currBeast = option - 1;

    //output success message to player
    cout << "Swapped to " << player.party[player.currBeast].nickName << '!' << endl << endl;

    return true;
}