#include "elebeastClass.h"

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

    newBeast.nickName = newBeast.base.name[0];

    fin.close( );

    return true;
}