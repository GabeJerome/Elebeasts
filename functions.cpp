#include "trainer.h"



int find( int arr[], int tgt, int n )
{
    int i;

    for ( i = 0; i < n; i++ )
    {
        if ( arr[i] == tgt )
            return i;
    }

    return -1;
}



bool enterHeals( trainer &me )
{
    int i, j;
    int totalHeals = 0;
    bool valid = false;
    int healInput = -1, beastInput = 6;
    string heals[3] = { "Small", "Medium", "Large" };

    //choose a heal and choose a beast to use it on
    while ( beastInput == 6 )
    {
        cout << "Which one would you like to use?" << endl;

        for ( i = 0; i < 3; i++ )
        {
            for ( j = 0; j < 20; j++ )
            {
                if ( me.bag.heals[i][j] == 1 )
                    totalHeals++;
            }

            cout << i + 1 << ' ' << heals[i] << ": " << totalHeals << endl;
            totalHeals = 0;
        }

        cout << i + 1 << " Back" << endl;

        while ( !valid )
        {
            cin >> healInput;

            if ( healInput == i + 1 )
                return false;

            if ( healInput < 1 || healInput > 4 )
                cout << "Invalid option. Please choose 1 - 4." << endl;
            else if ( find( me.bag.heals[healInput - 1], 1, 20 ) == -1 )
                cout << "You don't have any of those! Choose another." << endl;
            else
                valid = true;
        }
        valid = false;

        cout << "Which beast will you use it on?" << endl;
        me.printParty( );
        cout << "6: Back" << endl;

        while ( !valid )
        {
            cin >> beastInput;
            
            if ( beastInput == 6 )
                valid = true;
            else if ( beastInput < 1 || beastInput > 5 )
                cout << "Invalid option. Please choose a beast in your party." << endl;
            else if ( me.party[beastInput - 1].base.ID == -1 )
                cout << "There is no beast in that spot. Try again." << endl;
            else valid = true;
        }
        if ( !me.heal( beastInput - 1, healInput - 1 ) )
            beastInput = 6;
        valid = false;
    }

    me.printParty( );
        
    return true;
}



bool enterBalls( trainer &me )
{
    int i, j;
    int totalBalls = 0;
    bool valid = false;
    int input = -1;
    string balls[3] = { "Decent Balls", "Good Balls", "Great Balls" };

    for ( i = 0; i < 3; i++ )
    {
        for ( j = 0; j < 30; j++ )
        {
            if ( me.bag.balls[i][j] == 1 )
                totalBalls++;
        }

        cout << i + 1 << ' ' << balls[i] << ": " << totalBalls << endl;
        totalBalls = 0;
    }

    cout << i + 1 << " Back" << endl;


    while ( !valid )
    {
        cin >> input;

        if ( input == i + 1 )
            return false;

        if ( input < 1 || input > 3 )
            cout << "Invalid option. Please choose 1 - 4." << endl;
        else if ( find( me.bag.balls[input - 1], 1, 20 ) == -1 )
            cout << "You don't have any of those! Choose another." << endl;
        else
            valid = true;
    }

    me.captureBeast( me.currOpponent, input - 1 );

    return true;
}