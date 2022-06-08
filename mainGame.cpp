#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "header.h"

const bool RUNCATCH = true;

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

    /*cout << "Welcome to the realm of Elebeasts!" << endl << endl;
    while (menuOption != 1 && menuOption != 2)
    {
        cout << "Enter 1 to start a new game or enter 2 to load your file: ";
        cin >> menuOption;
        if (menuOption != 1 && menuOption != 2)
            cout << "That's not a valid option!" << endl << endl;
    }*/


}