#include "header.h"

using namespace std;



//TODO: write function to unpackage binary data
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
        for ( i = 0; i < 3; i++ )
        {
            fin.get( temp.name[i], 16, ' ' );
            fin.ignore( );
        }
        for ( i = 0; i < 3; i++ )
            fin >> temp.health[i];
        for ( i = 0; i < 3; i++ )
            fin >> temp.defense[i];
        for ( i = 0; i < 3; i++ )
            fin >> temp.spdefense[i];
        for ( i = 0; i < 3; i++ )
            fin >> temp.attack[i];
        for ( i = 0; i < 3; i++ )
            fin >> temp.spattack[i];
        for ( i = 0; i < 3; i++ )
            fin >> temp.speed[i];
        for ( i = 0; i < 3; i++ )
            fin >> temp.eleType1[i];
        for ( i = 0; i < 3; i++ )
            fin >> temp.eleType2[i];
        for ( i = 0; i < 3; i++ )
            fin >> temp.evolveLevel[i];

        i = 0;
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



bool getBeastData( beast &newBeast, int beastID )
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

    fin.close( );

    return true;
}