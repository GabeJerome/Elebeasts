#include "trainer.h"
#include "header.h"

using namespace std;



bool storeBeastDataBinary( )
{
    baseStats temp;
    int i;
    ifstream fin;
    ofstream fout;

    fin.clear( );
    fout.clear( );

    fin.open( "beastData.txt" );
    if ( !fin.is_open( ) )
    {
        cout << "Could not open file: beastData.txt" << endl;
        return false;
    }

    fout.open( "beastData.bin", ios::out | ios::trunc | ios::binary );
    if ( !fout.is_open( ) )
    {
        cout << "Could not open file: beastDataBin.txt" << endl;
        return false;
    }

    while ( fin.peek( ) != EOF )
    {
        i = 0;

        fin >> temp.ID;
        fin.ignore( );
        fin.get( temp.name, 16, ' ' );
        fin >> temp.health;
        fin >> temp.defense;
        fin >> temp.spdefense;
        fin >> temp.attack;
        fin >> temp.spattack;
        fin >> temp.speed;
        fin >> temp.eleType1;
        fin >> temp.eleType2;
        fin >> temp.evolveLevel;

        while ( fin.peek( ) != ':' )
        {
            fin >> temp.moveSet[i];
            i++;
        }

        fin.ignore( );
        fin.ignore( );

        for ( i = i; i < 30; i++ )
            temp.moveSet[i] = 0;

        fout.write( (char *)&temp, sizeof( baseStats ) );
    }

    fin.close( );
    fout.close( );

    return true;
}



bool getData( beast &newBeast, int beastID )
{
    ifstream fin;
    int i;

    fin.open( "beastData.bin", ios::in | ios::binary );
    if ( !fin.is_open( ) )
    {
        cout << "Could not open file: beastData.bin" << endl;
        return false;
    }

    fin.clear( );
    fin.seekg( ( static_cast<unsigned long long>( beastID ) - 1 ) * sizeof( baseStats ), ios::beg );
    fin.read( (char *)&newBeast.base, sizeof( baseStats ) );

    for ( i = 0; i < 16; i++ )
        newBeast.nickName[i] = newBeast.base.name[i];

    newBeast.currentHealth = newBeast.getMaxHP( );

    fin.close( );

    return true;
}



bool storeMoveDataBinary( )
{
    Move temp;
    ifstream fin;
    ofstream fout;

    fin.clear( );
    fout.clear( );

    fin.open( "moveData.txt" );
    if ( !fin.is_open( ) )
    {
        cout << "Could not open file: moveData.txt" << endl;
        return false;
    }

    fout.open( "moveData.bin", ios::out | ios::trunc | ios::binary );
    if ( !fout.is_open( ) )
    {
        cout << "Could not open file: moveDataBin.txt" << endl;
        return false;
    }

    while ( fin.peek( ) != EOF )
    {
        fin.get( temp.name, 20, ' ' );
        fin >> temp.type;
        fin >> temp.element;
        fin >> temp.power;
        fin >> temp.accuracy;

        fout.write( (char *)&temp, sizeof( Move ) );

        fin.ignore( );
    }

    fin.close( );
    fout.close( );

    return true;
}



bool getData( Move &newMove, int moveID )
{
    ifstream fin;
    fin.open( "moveData.bin", ios::in | ios::binary );
    if ( !fin.is_open( ) )
    {
        cout << "Could not open file: moveData.bin" << endl;
        return false;
    }
    fin.clear( );
    fin.seekg( ( static_cast<unsigned long long>( moveID ) - 1 ) * sizeof( Move ), ios::beg );
    fin.read( (char *)&newMove, sizeof( Move ) );

    fin.close( );

    return true;
}



bool saveFile( trainer &player, int num )
{
    string fileName = "Save";
    char saveNum = num + 48;
    ofstream fout;

    fileName = fileName + saveNum + ".bin";

    fout.open( fileName, ios::out | ios::binary | ios::trunc );
    if ( !fout.is_open( ) )
    {
        cout << "Could not open save file " << num << endl;
        return false;
    }

    fout.seekp( ios::beg, 0 );
    fout.write( (char *)&player, sizeof( trainer ) );

    cout << "Successfully saved to Save" << num << ".bin" << endl;

    return true;
}



bool loadFile( trainer &player, int num )
{
    string fileName = "Save";
    char saveNum = num + 48;
    ifstream fin;

    fileName = fileName + saveNum + ".bin";

    fin.open( fileName, ios::in | ios::binary );
    if ( !fin.is_open( ) )
    {
        cout << "Could not load save file " << num << '.' << endl;
        return false;
    }

    if ( fin.peek( ) == EOF )
        return false;

    fin.seekg( ios::beg, 0 );
    fin.read( (char *)&player, sizeof( trainer ) );

    return true;
}



void deleteFile( )
{
    int fileNum;
    char saveNum;
    string fileName = "Save";
    ofstream fout;
    bool valid = false, valid2 = false;
    int i, option;
    trainer testPlayer;

    while ( !valid )
    {
        cout << endl << endl;
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

        cout << "4: back" << endl;

        cout << "Enter the number of the file you want to delete." << endl;
        cin >> fileNum;

        if ( fileNum == 4 )
            return;

        if ( fileNum < 1 || fileNum > 3 )
            cout << "That is not valid option." << endl;
        else
        {
            while ( !valid2 )
            {
                cout << "Are you sure you want to delete Save File " << fileNum << endl;
                cout << "1: Yes\n2: No" << endl;
                cin >> option;

                if ( option == 1 )
                    valid = valid2 = true;
                else if ( option == 2 )
                    valid2 = true;
                else
                    cout << "That is not a valid option" << endl;
            }
        }
        valid2 = false;
    }

    saveNum = fileNum + 48;

    fileName = fileName + saveNum + ".bin";

    fout.open( fileName, ios::binary | ios::trunc );
    if ( !fout.is_open( ) )
        cout << "Could not delete " << fileName << endl;

    fout.close( );
}