#include "header.h"

using namespace std;



//TODO: write function to unpackage binary data
void storeBeastDataBinary( ifstream &fin, ofstream &fout )
{
    baseStats temp;
    int i;

    while ( fin.peek( ) != EOF )
    {
        for ( i = 0; i < 3; i++ )
        {
            fin.get( temp.name, 16, ' ' );
            fin >> temp.health[i];
            fin >> temp.defense[i];
            fin >> temp.spdefense[i];
            fin >> temp.attack[i];
            fin >> temp.spattack[i];
            fin >> temp.speed[i];
            fin >> temp.eleType1[i];
            fin >> temp.eleType2[i];
            fin >> temp.evolveLevel[i];


        }

        while ( fin.peek( ) != ':' )
        {
            fin >> temp.moveSet[i];
            i++;
        }

        fin.ignore( );
        fin.ignore( );

        i = 0;
        for ( i = i; i < 50; i++ )
            temp.moveSet[i] = 0;

        fout.write( (char *)&temp, sizeof( baseStats ) );
    }
}