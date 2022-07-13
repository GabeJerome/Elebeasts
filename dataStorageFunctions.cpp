#include "trainer.h"

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

        for ( i = i; i < 50; i++ )
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
    fin.open( "beastData.bin", ios::in | ios::binary );
    if ( !fin.is_open( ) )
    {
        cout << "Could not open file: beastData.bin" << endl;
        return false;
    }
    fin.clear( );
    fin.seekg( ( beastID - 1 ) * sizeof( baseStats ), ios::beg );
    fin.read( (char *)&newBeast.base, sizeof( baseStats ) );

    strcpy_s( newBeast.nickName, 16, newBeast.base.name );

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
    fin.seekg( ( moveID - 1 ) * sizeof( Move ), ios::beg );
    fin.read( (char *)&newMove, sizeof( Move ) );

    fin.close( );

    return true;
}