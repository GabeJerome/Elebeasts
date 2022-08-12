#include "header.h"



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



bool enterHeals( trainer &player )
{
    int i, j;
    int totalHeals = 0;
    bool valid = false;
    int healInput = -1, beastInput = 6;
    string heals[3] = { "Small", "Medium", "Large" };

    cout << endl;

    //choose a heal and choose a beast to use it on
    while ( beastInput == 6 )
    {
        cout << "Which one would you like to use?" << endl;

        for ( i = 0; i < 3; i++ )
        {
            for ( j = 0; j < 20; j++ )
            {
                if ( player.bag.heals[i][j] == 1 )
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
            else if ( find( player.bag.heals[healInput - 1], 1, 20 ) == -1 )
                cout << "You don't have any of those! Choose another." << endl;
            else
                valid = true;
        }
        valid = false;

        cout << endl;

        cout << "Which beast will you use it on?" << endl;
        player.printParty( );
        cout << "6: Back" << endl;

        while ( !valid )
        {
            cin >> beastInput;
            
            if ( beastInput == 6 )
                valid = true;
            else if ( beastInput < 1 || beastInput > 5 )
                cout << "Invalid option. Please choose a beast in your party." << endl;
            else if ( player.party[beastInput - 1].base.ID == -1 )
                cout << "There is no beast in that spot. Try again." << endl;
            else valid = true;
        }
        if ( !player.heal( beastInput - 1, healInput - 1 ) )
            beastInput = 6;
        valid = false;
    }

    cout << endl;

    player.printParty( );

    cout << endl;
        
    return true;
}



bool enterBalls( trainer &player )
{
    int i, j;
    int totalBalls = 0;
    bool valid = false;
    int input = -1;
    string balls[3] = { "Decent Balls", "Good Balls", "Great Balls" };

    cout << endl;

    for ( i = 0; i < 3; i++ )
    {
        for ( j = 0; j < 30; j++ )
        {
            if ( player.bag.balls[i][j] == 1 )
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
        else if ( player.currOpponent.base.ID == -1 )
            cout << "You can't use that here!" << endl;
        else if ( find( player.bag.balls[input - 1], 1, 20 ) == -1 )
            cout << "You don't have any of those! Choose another." << endl;
        else if ( !player.inWildBattle )
            cout << "You can only catch wild beasts!" << endl;
        else
            valid = true;
    }

    cout << endl;

    player.captureBeast( input - 1 );

    cout << endl;

    return true;
}



bool checkLoss( trainer &player )
{
    int i;

    for ( i = 0; i < 5; i++ )
    {
        //if there is a beast in this spot and it has more than zero health
        if ( player.party[i].base.ID != -1 && player.party[i].currentHealth != 0 )
            return false;
    }

    return true;
}



void healthBar( beast curr )
{
    int i = 0;
    float healthPercent = float( curr.currentHealth ) / float( curr.getMaxHP( ) );
    int numBars = int( healthPercent * 25 );

    while ( curr.nickName[i] != '\0' )
    {
        cout << ' ';
        i++;
    }
    cout << "   ";
    for ( i = 0; i < 25; i++ )
        cout << char( 95 );
    cout << ' ' << endl;

    cout << curr.nickName << ": ";
    cout << char( 179 );
    for ( i = 0; i < numBars; i++ )
        cout << char( 219 );
    for ( i = i; i < 25; i++ )
        cout << ' ';
    cout << char( 179 ) << endl;

    cout << "lvl " << curr.getLevel( );

    i = 0;
    while ( curr.nickName[i] != '\0' )
    {
        cout << ' ';
        i++;
    }
    cout << setw( 14 );
    cout << curr.currentHealth << '/' << curr.getMaxHP( ) << endl;
}



void printLine( )
{
    int i;

    for ( i = 0; i < 40; i++ )
    {
        cout << char( 205 );
    }
}



void tutorial( trainer &player )
{
    bool valid = false;
    int option = 0;
    beast starter;

    cout << "Welcome to the realm of Elebeasts!" << endl << endl;;
    cout << "Here, you battle with your beasts to become the best" <<
        " beast master in the land!" << endl << endl;

    getPlayerName( player );

    cout << "Okay " << player.name << ". " << "Your first step is to " << 
        "choose which beast you want to begin" <<
        " your adventure with. (enter 1, 2, or 3)" << endl << endl;
    while ( !valid )
    {
        cout << "1: Flacora - The fire pup" << endl;
        cout << "2: Stropie - The water reptile" << endl;
        cout << "3: Fotosin - The grass dinosaur" << endl << endl;

        cin >> option;

        if ( option < 1 || option > 3 )
            cout << "Invalid option. Choose 1, 2, or 3" << endl << endl;
        else
            valid = true;
    }
    valid = false;

    if ( option == 1 )
        getData( starter, 1 );
    else if ( option == 2 )
        getData( starter, 4 );
    else
        getData( starter, 7 );

    player.party[0] = starter;

    cout << "You chose " << starter.nickName << '.' << endl;

    while ( !valid )
    {
        cout << "Would you like to give your beast a nick name?" << endl;
        cout << "1: Yes\n2: No" << endl;

        cin >> option;

        if ( option == 1 )
        {
            giveNickname( player );
            valid = true;
        }
        else if ( option == 2 )
            valid = true;
        else
            cout << "Please choose 1 or 2" << endl;
    }
    
    cout << "You and " << player.party[0].nickName << " will now begin your adventure!" << endl << endl;
}



void giveNickname( trainer &player )
{
    bool valid = false, valid2 = false;
    int option = -1;
    int i;
    string name;

    while ( !valid )
    {
        cout << "Enter a nick name. (max 15 characters)" << endl;

        cin >> name;

        if ( name.size( ) > 15 )
            cout << "That name is too long." << endl;
        else
        {
            valid2 = false;
            while ( !valid2 )
            {
                cout << "Are you sure you want to go with " << name << "?" << endl;
                cout << "1: Yes\n2: No" << endl;
                cin >> option;

                if ( option == 1 )
                    valid = valid2 = true;
                else if ( option != 2 )
                    cout << "That is not a valid option." << endl;
                else
                    valid2 = true;
            }
        }
    }

    for ( i = 0; i < name.size( ); i++ )
    {
        player.party[0].nickName[i] = name[i];
    }

    while ( i < 16 )
    {
        player.party[0].nickName[i] = '\0';
        i++;
    }
}

void getPlayerName( trainer &player )
{
    bool valid = false, valid2 = false;
    int i;
    int option = -1;
    string name;

    while ( !valid )
    {
        cout << "Enter your name. (max 15 characters)" << endl;

        cin >> name;

        if ( name.size( ) > 15 )
            cout << "That name is too long." << endl;
        else
        {
            valid2 = false;
            while ( !valid2 )
            {
                cout << "Your name is " << name << "?" << endl;
                cout << "1: Yes\n2: No" << endl;
                
                cin >> option;

                if ( option == 1 )
                    valid = valid2 = true;
                else if ( option != 2 )
                    cout << "That is not a valid option." << endl;
                else
                    valid2 = true;
            }
        }
    }

    for ( i = 0; i < name.size( ); i++ )
    {
        player.name[i] = name[i];
    }

    while ( i < 16 )
    {
        player.name[i] = '\0';
        i++;
    }
}



void chooseFile( trainer &player )
{
    int i;
    trainer testPlayer;
    int fileNum;
    bool valid = false;

    cout << "Which file would you like to load?" << endl << endl;
    for ( i = 1; i < 4; i++ )
    {
        cout << "Save File " << i << ": " << endl;
        if ( loadFile( testPlayer, i ) )
        {
            cout << testPlayer.name << endl;
            testPlayer.printParty( );
        }
        else
            cout << "New Game" << endl;
        cout << endl;
    }

    while ( !valid )
    {
        cout << "Enter a file number: ";
        cin >> fileNum;

        if ( fileNum < 1 || fileNum > 3 )
            cout << "That is not a valid input (choose 1, 2, or 3)" << endl;
        else
            valid = true;
    }

    if ( loadFile( player, fileNum ) )
    {
        cout << "File " << fileNum << " loading..." << endl;
        this_thread::sleep_for( chrono::seconds( 3 ) );
        cout << "Welcom back " << player.name << '!' << endl;
        valid = true;
    }
    else
    {
        tutorial( player );
        valid = true;
    }
}



void printTitle( )
{
    int i;

    for ( i = 0; i < 58; i++ )
        cout << char( 205 );
    cout << endl << setw( 10 ) << char( 218 ) << char( 196 ) << char( 196 ) << char( 196 );

    cout << endl << setw( 10 ) << char( 179 ) << setw( 5 );

    cout << endl << setw( 10 ) << char( 195 ) << char( 196 ) << char( 196 ) << setw( 3 ) << char( 179 ) << setw( 3 ) << char( 218 ) << char( 196 ) << char( 196 ) << setw( 2 ) << char( 218 ) << char( 196 ) << char( 191 ) << setw( 2 ) << char( 218 ) << char( 196 ) << char( 196 ) << setw(2) << char(218 ) << char(196 ) << char( 196 ) << char( 191 ) << setw(2) << char(218 ) << char( 196 ) << char( 196 ) << char( 191 ) << setw(2) << char( 218 ) << char( 196 ) << char( 194 ) << char( 196 ) << char( 191 ) << setw( 2 ) << char( 218 ) << char( 196 ) << char( 196 ) << char( 191 );

    cout << endl << setw( 10 ) << char( 179 ) << setw( 5 ) << char( 179 ) << setw(3 ) << char(195 ) << char(196 ) << setw(3) << char( 195 ) << char(196 ) << char(193 ) << char(191 ) << char( 195 ) << char( 196 ) << setw(3) << char(195 ) << char( 196 ) << char( 196 ) << char( 180 ) << setw(2) << char( 192 ) << char( 196 ) << char( 196 ) << char( 191 ) << setw(4) << char( 179 ) << setw( 4 ) << char( 192 ) << char( 196 ) << char( 196 ) << char( 191 );

    cout << endl << setw( 10 ) << char( 192 ) << char( 196 ) << char( 196 ) << char( 196 ) << " " << char( 192 ) << char( 196 ) << setw(2 ) << char( 192 ) << char(196 ) << char(196 ) << setw(2) << char( 192 ) << char(196 ) << char(196 ) << char( 217 ) << char( 192 ) << char( 196 ) << char( 196 ) << setw( 2 ) << char( 193 ) << setw(3) << char( 193 ) << setw(2) << char( 192 ) << char( 196 ) << char( 196 ) << char( 217 ) << setw(4) << char( 193 ) << setw( 4 ) << char( 192 ) << char( 196 ) << char( 196 ) << char( 217 );

    cout << endl;
    for ( i = 0; i < 58; i++ )
        cout << char( 205 );

    cout << endl;
}



void generateRandBeast( trainer player, beast &randBeast )
{
    int maxExp = player.party[0].getExp( );
    int lowExpBound, highExpBound;
    int i;
    random_device rand;
    int randExp, randID;

    for ( i = 1; i < 5; i++ )
    {
        if ( maxExp < player.party[i].getExp( ) )
        {
            maxExp = player.party[i].getExp( );
        }
    }

    lowExpBound = int( maxExp - ( maxExp * ( 2 / cbrt( maxExp ) ) ) );
    highExpBound = int( maxExp + ( maxExp * ( 5 / cbrt( maxExp ) ) ) );

    randExp = ( rand( ) % ( highExpBound - lowExpBound ) + 1 ) + lowExpBound;

    randID = ( rand( ) % TOTAL_BEASTS ) + 1;

    randBeast.setExp( randExp );

    getData( randBeast, randID );

    findEvolution( randBeast );

    randBeast.writeLearnSet( randBeast.base.moveSet );
    randBeast.learnMoves( );
}



void findEvolution( beast &randBeast )
{
    beast belowBeast;

    getData( randBeast, randBeast.base.ID );

    if ( randBeast.base.ID != 1 )
        getData( belowBeast, randBeast.base.ID - 1 );
    else
        getData( belowBeast, randBeast.base.ID );


    if ( randBeast.getLevel( ) >= randBeast.base.evolveLevel )
    {
        randBeast.base.ID++;
        return findEvolution( randBeast );
    }

    if ( belowBeast.base.evolveLevel != 101 && randBeast.getLevel( ) < belowBeast.base.evolveLevel )
    {
        randBeast.base.ID--;
        return findEvolution( randBeast );
    }
}



int displayWorldOptions( )
{
    int option = -1;

    while ( true )
    {
        cout << "What would you like to do?" << endl;
        cout << "1: Battle" << endl;
        cout << "2: Bag" << endl;
        cout << "3: Shop" << endl;
        cout << "4: Beasts" << endl;

        cin >> option;

        if ( option > 0 && option < 5 )
            return option;
        else
            cout << "That is not a valid input." << endl << endl;
    }
}



void playerBattle( trainer &player )
{
    int option = -1;
    bool valid = false;
    battle currBattle;

    while ( !valid )
    {
        cout << "What kind of battle do you want to do?" << endl;
        cout << "1: Wild Battle" << endl;
        cout << "2: Trainer Battle" << endl;
        cout << "3: Boss Battle" << endl;
        cout << "4: Back" << endl;

        cin >> option;

        if ( option == 4 )
            return;

        if ( option > 0 && option < 4 )
            valid = true;
        else
            cout << "That is not a valid input." << endl << endl;
    }

    if ( option == 1 )
        currBattle.wildBattle( player );
    //continue creating more battles and testing
}
