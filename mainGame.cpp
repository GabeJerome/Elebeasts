#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "header.h"

const bool RUNCATCH = false;

int main( )
{
    Catch::Session session;
    int result;

    if ( RUNCATCH )
    {
        result = session.run( );
        if ( result != 0 )
        {
            cout << "Test cases didn't pass." << endl;
            return result;
        }
    }


    int option = 0;
    trainer player;
    bool valid = false;
    beast starter;
    int fileNum;

    
    printTitle( );

    do 
    {
        cout << '\n' << "Press enter to start...";
    } while ( !cin.get( ) );

    fileNum = chooseFile( player );

    cout << endl << endl;


    while ( true )
    {
        option = displayWorldOptions( player );

        if ( option == 1 )
            playerBattle( player );
        else if ( option == 2 )
            player.enterBag( );
        else if ( option == 3 )
            enterShop( player );
        else if ( option == 4 )
            player.printParty( );
        else if ( option == 5 )
            healAllBeasts( player, 300 );
        else if ( option == 6 )
        {
            cout << "Saving progress to Save" << fileNum << ".bin..." << endl;
            saveFile( player, fileNum );
            return 0;
        }
        else
            cout << "That is not a valid option." << endl;

        if ( checkLoss( player ) )
            healAllBeasts( player, 0 );

        saveFile( player, fileNum );
    }

    return 0;
}