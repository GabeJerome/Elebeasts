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


    int menuOption = 0;
    int option = 0;
    trainer player;
    bool valid = false;
    beast starter;

    
    while (menuOption != 1 && menuOption != 2)
    {
        cout << "Enter 1 to start a new game or enter 2 to load your file: ";
        cin >> menuOption;
        if (menuOption != 1 && menuOption != 2)
            cout << "That's not a valid option!" << endl << endl;
    }

    if ( menuOption == 1 )
        tutorial( player );
    else
    {
        cout << "Which file would you like to load?" << endl;
        //display files 1, 2, and 3 with trainer names beside each.
    }
}