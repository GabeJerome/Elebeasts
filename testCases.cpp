#include "catch.hpp"
#include "header.h"



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
    beast fireBeast( Flacora ), waterBeast( Stropie );

    fireBeast.fight( fireBeast.move[0], waterBeast );

    REQUIRE( true );
}



TEST_CASE( "gainExp" )
{
    beast Beast1( Stropie ), Beast2( Flacora );
    int originalExp = Beast1.getExp( );

    Beast1.gainExp( Beast2 );

    REQUIRE( Beast1.getExp( ) > originalExp );
}



TEST_CASE( "getLevel" )
{
    SECTION( "level 1 lower" )
    {
        beast testBeast( "Flacora", 0, 40, 40, 45, 48, 53, 60, 65, fire, 2, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 1 );
    }
    SECTION( "level 1 upper" )
    {
        beast testBeast( "Flacora", 7, 40, 40, 45, 48, 53, 60, 65, fire, 2, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 1 );
    }
    SECTION( "level 2 lower" )
    {
        beast testBeast( "Flacora", 8, 40, 40, 45, 48, 53, 60, 65, fire, 2, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 2 );
    }
    SECTION( "level 2 upper" )
    {
        beast testBeast( "Flacora", 26, 40, 40, 45, 48, 53, 60, 65, fire, 2, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 2 );
    }
    SECTION( "level 3 lower" )
    {
        beast testBeast( "Flacora", 27, 40, 40, 45, 48, 53, 60, 65, fire, 2, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 3 );
    }
    SECTION( "level 71" )
    {
        beast testBeast( "Flacora", 365346, 40, 40, 45, 48, 53, 60, 65, fire, 2, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 71 );
    }
    SECTION( "level 99" )
    {
        beast testBeast( "Flacora", 970300, 40, 40, 45, 48, 53, 60, 65, fire, 2, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 99 );
    }
    SECTION( "level 100" )
    {
        beast testBeast( "Flacora", 1043023, 40, 40, 45, 48, 53, 60, 65, fire, 2, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 100 );
    }
}


//TODO: FINISH THESE TEST CASES BEFORE ANYTHING ELSE

TEST_CASE( "get functions" )
{
    SECTION( "level 1" )
    {
        beast testBeast( Fotosin );

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
        beast testBeast( "Fotosin", 39521, 43, 43, 50, 64, 50, 63, 43, grass, 2, flacoraLearnSet );

        REQUIRE( testBeast.getLevel( ) == 34 );
        REQUIRE( testBeast.getExp( ) == 39521 );
        REQUIRE( testBeast.getMaxHP( ) == 73 );
        REQUIRE( testBeast.getCurrHP( ) == 73 );
        REQUIRE( testBeast.getDef( ) == 39 );
        REQUIRE( testBeast.getSpDef( ) == 48 );
        REQUIRE( testBeast.getAtt( ) == 39 );
        REQUIRE( testBeast.getSpAtt( ) == 47 );
        REQUIRE( testBeast.getSpeed( ) == 34 );
        REQUIRE( testBeast.getType( ) == "grass" );
    }

}



TEST_CASE( "effectiveness and multiple moves" )
{
    beast fireBeast( Flacora ), waterBeast( Stropie );

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

    beast fireBeast(Flacora), grassBeast(Fotosin);

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
    beast beast1( Flacora );

    beast1.printMoves( );

    REQUIRE( true );
}



TEST_CASE( "levelUp" )
{
    beast beast1( "Flacora", 111, 40, 40, 45, 48, 53, 60, 65, fire, 2, flacoraLearnSet );
    beast beast2( "Flacora", 200, 40, 40, 45, 48, 53, 60, 65, fire, 2, flacoraLearnSet );

    beast1.gainExp( beast2 );

    REQUIRE( true );
}