#pragma once
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "battle.h"

using namespace std;

const int TOTAL_BEASTS = 9;

bool saveFile( trainer &player, int num );

bool loadFile( trainer &player, int num );

void tutorial( trainer &player );

void giveNickname( trainer &player );

void getPlayerName( trainer &player );

void chooseFile( trainer &player );

void printTitle( );

void findEvolution( beast &randBeast );

void generateRandBeast( trainer player, beast &randBeast );