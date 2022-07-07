#include "catch.hpp"
#include "header.h"

enum beastID { Flacora = 1, Firectric, Volcorage,
               Stropie, Apolozard, Reptide, 
               Fotosin, Synthescor, DSrakosis };

TEST_CASE( "random_device test" )
{
    std::random_device hit;
    unsigned int min, max, val;
    bool pass = false;
    int i;

    min = 1;
    max = 100;

    for ( i = 0; i < 100; i++ )
    {
        val = ( hit( ) % 100 ) + 1;

        if ( val <= max && val >= min )
            pass = true;

        REQUIRE( pass );
    }
}



TEST_CASE( "fight" )
{
    beast fireBeast(1, Flacora ), waterBeast(1, Stropie );

    fireBeast.fight( fireBeast.move[0], waterBeast );

    REQUIRE( true );
}



TEST_CASE( "gainExp" )
{
    beast Beast1( 1, Stropie ), Beast2( 1, Flacora );
    int originalExp = Beast1.getExp( );

    Beast1.gainExp( Beast2 );

    REQUIRE( Beast1.getExp( ) > originalExp );
}



TEST_CASE( "getLevel" )
{
    const short int flacoraLearnSet[50] = { 0, 261, 0 };
    SECTION( "level 1 lower" )
    {
        beast testBeast( "Flacora", 0, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, 0, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 1 );
    }
    SECTION( "level 1 upper" )
    {
        beast testBeast( "Flacora", 7, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, 0, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 1 );
    }
    SECTION( "level 2 lower" )
    {
        beast testBeast( "Flacora", 8, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, 0, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 2 );
    }
    SECTION( "level 2 upper" )
    {
        beast testBeast( "Flacora", 26, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, 0, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 2 );
    }
    SECTION( "level 3 lower" )
    {
        beast testBeast( "Flacora", 27, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, 0, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 3 );
    }
    SECTION( "level 71" )
    {
        beast testBeast( "Flacora", 365346, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, 0, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 71 );
    }
    SECTION( "level 99" )
    {
        beast testBeast( "Flacora", 970300, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, 0, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 99 );
    }
    SECTION( "level 100" )
    {
        beast testBeast( "Flacora", 1043023, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, 0, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 100 );
    }
}


//TODO: FINISH THESE TEST CASES BEFORE ANYTHING ELSE

TEST_CASE( "get functions" )
{
    SECTION( "level 1" )
    {
        beast testBeast( 1, Fotosin );
        testBeast.setExp( 0 );

        REQUIRE( testBeast.getLevel( ) == 1 );
        REQUIRE( testBeast.getExp( ) == 0 );
        REQUIRE( testBeast.getMaxHP( ) == 11 );
        REQUIRE( testBeast.getCurrHP( ) == 11 );
        REQUIRE( testBeast.getDef( ) == 6 );
        REQUIRE( testBeast.getSpDef( ) == 6 );
        REQUIRE( testBeast.getAtt( ) == 6 );
        REQUIRE( testBeast.getSpAtt( ) == 6 );
        REQUIRE( testBeast.getSpeed( ) == 5 );
        REQUIRE( testBeast.getType( ) == "grass" );
    }
    SECTION( "level 34" )
    {
        beast testBeast( 1, Fotosin );
        testBeast.setExp( 39521 );

        REQUIRE( testBeast.getLevel( ) == 34 );
        REQUIRE( testBeast.getExp( ) == 39521 );
        REQUIRE( testBeast.getMaxHP( ) == 73 );
        REQUIRE( testBeast.getDef( ) == 39 );
        REQUIRE( testBeast.getSpDef( ) == 45 );
        REQUIRE( testBeast.getAtt( ) == 47 );
        REQUIRE( testBeast.getSpAtt( ) == 42 );
        REQUIRE( testBeast.getSpeed( ) == 34 );
        REQUIRE( testBeast.getType( ) == "grass" );
    }

}



TEST_CASE( "effectiveness and multiple moves" )
{
    beast fireBeast( 1, Flacora ), waterBeast( 1, Stropie );

    fireBeast.changeMove( 0, cinder );
    fireBeast.changeMove( 1, swipe );
    waterBeast.changeMove( 0, dowse );

    fireBeast.fight( fireBeast.move[0], waterBeast );
    waterBeast.fight( waterBeast.move[0], fireBeast );
    fireBeast.fight( fireBeast.move[1], waterBeast );

    REQUIRE( true );
}



TEST_CASE("runAway")
{
    bool success = false;

    beast fireBeast(5, Flacora), grassBeast(1, Fotosin);

    REQUIRE(fireBeast.runAway( grassBeast ) == true);

    while ( success == false )
        success = grassBeast.runAway( fireBeast );

    REQUIRE( success );
}



TEST_CASE( "bit mask testing" )
{
    short int moves[2] = { 0, 642 };
    int moveAns[2] = { 0, 2 }, lvlAns[2] = { 0, 5 };
    short int move, level;
    int i;
    int num;

    
    for ( i = 0; i < 2; i++ )
    {
        num = moves[i];

        move = num & 127;
        num >>= 7;

        level = num & 511;

        REQUIRE( move == moveAns[i] );
        REQUIRE( level == lvlAns[i] );
    }
}



TEST_CASE( "Print Moves" )
{
    beast beast1( 1, Flacora );

    beast1.printMoves( );

    REQUIRE( true );
}



TEST_CASE( "levelUp" )
{
    const short int flacoraLearnSet[50] = { 0, 261, 0 };

    beast beast1( "Flacora", 111, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, 0, flacoraLearnSet );
    beast beast2( "Flacora", 200, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, 0, flacoraLearnSet );

    //beast1.gainExp( beast2 );

    REQUIRE( true );
}


TEST_CASE( "printStats - move" )
{
    Move testMove( swipe );

    testMove.printStats( );

    REQUIRE( true );
}



TEST_CASE( "storeBeastDataBinary" )
{
    ifstream fin;
    ofstream fout;

    storeBeastDataBinary( );


    REQUIRE( true );
}



TEST_CASE( "reading beast data from file" )
{
    beast newBeast;
    ifstream fin;

    getBeastData( newBeast, 2 );

    REQUIRE( newBeast.base.health == 58 );

    getBeastData( newBeast, 8 );

    REQUIRE( newBeast.base.attack == 81 );
}



//TODO: Finish testing evolve function
TEST_CASE( "Evolve" )
{
    beast testBeast1;
    beast testBeast2;

    testBeast2.setExp( 6000000 );

    SECTION( "first to second evolution" )
    {
        getBeastData( testBeast1, 1 );

        testBeast1.changeName( "Gerald" );
        testBeast1.setExp( 3370 );

        testBeast1.gainExp( testBeast2 );

        REQUIRE( testBeast1.base.attack == 69 );
    }
    SECTION( "second to third evolution" )
    {
        getBeastData( testBeast1, 5 );

        testBeast1.changeName( "Henry" );
        testBeast1.setExp( 42870 );

        testBeast1.gainExp( testBeast2 );

        REQUIRE( testBeast1.base.speed == 91 );
    }
    SECTION( "third evolution should not evolve" )
    {
        getBeastData( testBeast1, 9 );

        testBeast1.changeName( "Peter" );
        testBeast1.setExp( 999999 );

        testBeast1.gainExp( testBeast2 );

        REQUIRE( testBeast1.base.spdefense == 92 );
    }
}