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
        val = hit( ) % 101;

        if ( val <= max && val >= min )
            pass = true;

        REQUIRE( pass );
    }
}



TEST_CASE( "fight" )
{
    beast fireBeast( Flacora ), waterBeast( Stropie );

    fireBeast.changeMove( 0, swipe );

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
        beast testBeast( "Flacora", 1, 0, 40, 40, 45, 48, 53, 60, 65, fire );
        REQUIRE( testBeast.getLevel( ) == 1 );
    }
    SECTION( "level 1 upper" )
    {
        beast testBeast( "Flacora", 1, 7, 40, 40, 45, 48, 53, 60, 65, fire );
        REQUIRE( testBeast.getLevel( ) == 1 );
    }
    SECTION( "level 2 lower" )
    {
        beast testBeast( "Flacora", 1, 8, 40, 40, 45, 48, 53, 60, 65, fire );
        REQUIRE( testBeast.getLevel( ) == 2 );
    }
    SECTION( "level 2 upper" )
    {
        beast testBeast( "Flacora", 1, 26, 40, 40, 45, 48, 53, 60, 65, fire );
        REQUIRE( testBeast.getLevel( ) == 2 );
    }
    SECTION( "level 3 lower" )
    {
        beast testBeast( "Flacora", 1, 27, 40, 40, 45, 48, 53, 60, 65, fire );
        REQUIRE( testBeast.getLevel( ) == 3 );
    }
    SECTION( "level 71" )
    {
        beast testBeast( "Flacora", 1, 365346, 40, 40, 45, 48, 53, 60, 65, fire );
        REQUIRE( testBeast.getLevel( ) == 71 );
    }
    SECTION( "level 99" )
    {
        beast testBeast( "Flacora", 1, 970300, 40, 40, 45, 48, 53, 60, 65, fire );
        REQUIRE( testBeast.getLevel( ) == 99 );
    }
    SECTION( "level 100" )
    {
        beast testBeast( "Flacora", 1, 1043023, 40, 40, 45, 48, 53, 60, 65, fire );
        REQUIRE( testBeast.getLevel( ) == 100 );
    }
}


//TODO: FINISH THESE TEST CASES BEFORE ANYTHING ELSE

/*TEST_CASE( "get functions" )
{
    beast testBeast( Fotosin );

    REQUIRE( testBeast.getLevel( ) == 1 );
    REQUIRE( testBeast.getExp( ) == 0 );
    REQUIRE( testBeast.getMaxHP( ) == 43 );
    REQUIRE( testBeast.getCurrHP( ) == 43 );
    REQUIRE( testBeast.getDef( ) == 50 );
    REQUIRE( testBeast.getSpDef( ) == 64 );
    REQUIRE( testBeast.getAtt( ) == 50 );
    REQUIRE( testBeast.getSpAtt( ) == 63 );
    REQUIRE( testBeast.getSpeed( ) == 43 );
    REQUIRE( testBeast.getType( ) == 10 );

}



TEST_CASE("effectiveness")



TEST_CASE("runAway")
{
    beast fireBeast(Flacora), waterBeast(Stropie);
}*/