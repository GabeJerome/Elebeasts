#pragma once
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "elebeastClass.h"

using namespace std;



struct beastStats
{
    char name[16];
    int exp;
    int maxHP;
    int def;
    int spdef;
    int att;
    int spatt;
    int spd;
    int type;
    short int moveSet[50] = { 0 };
};


void storeBeastDataBinary( ifstream &fin, ofstream &fout );