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


    int option = 0;
    trainer player;
    bool valid = false;
    beast starter;

    
    printTitle( );

    do 
    {
        cout << '\n' << "Press enter to start...";
    } while ( !cin.get( ) );

    chooseFile( player );

    cout << endl << endl;

    //Main menu complete, start game


    
    return 0;
}