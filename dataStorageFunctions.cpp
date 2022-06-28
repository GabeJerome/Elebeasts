#include "header.h"

using namespace std;



//TODO: finish storage of beast data in binary file
void storeBeastDataBinary( ifstream &fin, ofstream &fout )
{
    beastStats temp;
    int i;

    while ( fin.peek( ) != EOF)
    {
        i = 0;

        fin.get( temp.name, 16, ' ' );
        fin >> temp.exp;
        fin >> temp.maxHP;
        fin >> temp.def;
        fin >> temp.spdef;
        fin >> temp.att;
        fin >> temp.spatt;
        fin >> temp.spd;
        fin >> temp.type;
        while ( fin.peek( ) != ':' )
        {
            fin >> temp.moveSet[i];
            i++;
        }

        fin.ignore( );
        fin.ignore( );

        for ( i = i; i < 50; i++ )
            temp.moveSet[i] = 0;

        fout.write( (char *)&temp, sizeof( beastStats ) );
    }
}