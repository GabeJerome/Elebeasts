#include "catch.hpp"
#include "header.h"

enum beastID { Flacora = 1, Firectric, Volcorage,
               Stropie, Apolozard, Reptide, 
               Fotosin, Synthescor, Drakosis };


TEST_CASE( "Store Data" )
{
    storeMoveDataBinary( );
    storeBeastDataBinary( );
}

/*TEST_CASE( "random_device test" )
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

    fireBeast.attack( fireBeast.move[0], waterBeast );

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
    const short int flacoraLearnSet[50] = { 128, 389, 0 };
    SECTION( "level 1 lower" )
    {
        beast testBeast( "Flacora", 0, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 1 );
    }
    SECTION( "level 1 upper" )
    {
        beast testBeast( "Flacora", 7, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 1 );
    }
    SECTION( "level 2 lower" )
    {
        beast testBeast( "Flacora", 8, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 2 );
    }
    SECTION( "level 2 upper" )
    {
        beast testBeast( "Flacora", 26, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 2 );
    }
    SECTION( "level 3 lower" )
    {
        beast testBeast( "Flacora", 27, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 3 );
    }
    SECTION( "level 71" )
    {
        beast testBeast( "Flacora", 365346, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 71 );
    }
    SECTION( "level 99" )
    {
        beast testBeast( "Flacora", 970300, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 99 );
    }
    SECTION( "level 100" )
    {
        beast testBeast( "Flacora", 1043023, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, flacoraLearnSet );
        REQUIRE( testBeast.getLevel( ) == 100 );
    }
}



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

    Move cinder, swipe, dowse;

    getData( cinder, 3 );
    getData( swipe, 1 );
    getData( dowse, 4 );

    fireBeast.changeMove( 0, cinder );
    fireBeast.changeMove( 1, swipe );
    waterBeast.changeMove( 0, dowse );

    fireBeast.attack( fireBeast.move[0], waterBeast );
    waterBeast.attack( waterBeast.move[0], fireBeast );
    fireBeast.attack( fireBeast.move[1], waterBeast );

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
    const short int flacoraLearnSet[50] = { 128, 389, 0 };

    beast beast1( "Flacora", 111, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, flacoraLearnSet );
    beast beast2( "Flacora", 200, 40, 40, 45, 48, 53, 60, 65, fire, none, 101, flacoraLearnSet );

    //beast1.gainExp( beast2 );

    REQUIRE( true );
}


TEST_CASE( "printStats - move" )
{
    Move testMove;

    getData( testMove, 3 );

    testMove.printStats( );

    REQUIRE( true );
}



TEST_CASE( "storeBeastDataBinary" )
{
    storeBeastDataBinary( );

    REQUIRE( true );
}



TEST_CASE( "reading beast data from file" )
{
    beast newBeast;
    ifstream fin;

    getData( newBeast, 2 );

    REQUIRE( newBeast.base.health == 58 );

    getData( newBeast, 8 );

    REQUIRE( newBeast.base.attack == 81 );
}



TEST_CASE( "Evolve" )
{
    beast testBeast1;
    beast testBeast2;

    testBeast2.setExp( 6000000 );

    SECTION( "first to second evolution" )
    {
        getData( testBeast1, 1 );

        testBeast1.changeName( "Gerald" );
        testBeast1.setExp( 3370 );

        testBeast1.gainExp( testBeast2 );

        REQUIRE( testBeast1.base.attack == 69 );
    }
    SECTION( "second to third evolution" )
    {
        getData( testBeast1, 5 );

        testBeast1.setExp( 42870 );

        testBeast1.gainExp( testBeast2 );

        REQUIRE( testBeast1.base.speed == 91 );
    }
    SECTION( "third evolution should not evolve" )
    {
        getData( testBeast1, 9 );

        testBeast1.changeName( "Peter" );
        testBeast1.setExp( 999999 );

        testBeast1.gainExp( testBeast2 );

        REQUIRE( testBeast1.base.spdefense == 92 );
    }
}



TEST_CASE( "move data storage" )
{
    storeMoveDataBinary( );

    REQUIRE( true );
}



TEST_CASE( "reading move data from file" )
{
    Move newMove;

    SECTION( "Swipe" )
    {
        getData( newMove, 1 );


        REQUIRE( newMove.type == 1 );
        REQUIRE( newMove.element == 0 );
        REQUIRE( newMove.power == 20 );
        REQUIRE( newMove.accuracy == 100 );
    }
    SECTION( "Kick" )
    {
        getData( newMove, 2 );


        REQUIRE( newMove.type == 1 );
        REQUIRE( newMove.element == 0 );
        REQUIRE( newMove.power == 30 );
        REQUIRE( newMove.accuracy == 90 );
    }
    SECTION( "Cinder" )
    {
        getData( newMove, 3 );


        REQUIRE( newMove.type == 0 );
        REQUIRE( newMove.element == 1 );
        REQUIRE( newMove.power == 30 );
        REQUIRE( newMove.accuracy == 100 );
    }
    SECTION( "Dowse" )
    {
        getData( newMove, 4 );


        REQUIRE( newMove.type == 0 );
        REQUIRE( newMove.element == 2 );
        REQUIRE( newMove.power == 30 );
        REQUIRE( newMove.accuracy == 100 );
    }
    SECTION( "Thorn" )
    {
        getData( newMove, 5 );

        REQUIRE( newMove.type == 1 );
        REQUIRE( newMove.element == 3 );
        REQUIRE( newMove.power == 30 );
        REQUIRE( newMove.accuracy == 100 );
    }
}




TEST_CASE( "Capture Beast" )
{
    trainer me;
    beast testBeast( 4, Fotosin ), myBeast( 15, Synthescor );

    me.party[0] = myBeast;

    me.currOpponent = testBeast;

    me.captureBeast( great );

    REQUIRE( true );
}




TEST_CASE( "Bag" )
{
    trainer me;
    beast myBeast( 40, Reptide ), wildBeast( 30, Drakosis );

    me.party[0] = myBeast;

    wildBeast.attack( wildBeast.move[0], me.party[0] );

    me.giveHeals( 0, 11 );
    me.giveHeals( 2, 1 );

    me.giveBalls( 0, 24 );
    me.giveBalls( 2, 2 );

    me.enterBag( );

    REQUIRE( true );
}



TEST_CASE( "Fight" )
{
    trainer me;
    beast myBeast( 40, Reptide ), wildBeast( 37, Drakosis );

    me.party[0] = myBeast;

    me.currOpponent = wildBeast;
    me.fight( );
}



TEST_CASE( "healthBar" )
{
    beast myBeast( 40, Drakosis ), oppBeast( 40, Reptide );

    healthBar( myBeast );

    oppBeast.attack( oppBeast.move[0], myBeast );

    healthBar( myBeast );

    REQUIRE( true );
}



TEST_CASE( "wildBattle" )
{
    battle battle;
    trainer me;
    beast myBeast1( 40, Drakosis ), myBeast2( 41, Volcorage ), myBeast3( 34, Apolozard );
    beast oppBeast( 40, Reptide );

    me.party[0] = myBeast1;
    me.party[1] = myBeast2;
    me.party[2] = myBeast3;
    
    battle.wildBattle( me, oppBeast );

    REQUIRE( true );
}



TEST_CASE( "saveFile" )
{
    trainer me, me2;

    SECTION( "File 1" )
    {
        beast myBeast1( 40, Drakosis ), myBeast2( 41, Volcorage ), myBeast3( 34, Apolozard );

        me.party[0] = myBeast1;
        me.party[1] = myBeast2;
        me.party[2] = myBeast3;

        REQUIRE( saveFile( me, 1 ) );

        REQUIRE( loadFile( me2, 1 ) );

        me2.printParty( );
    }
    SECTION( "File 3" )
    {
        beast myBeast1( 94, Volcorage ), myBeast2( 88, Reptide ), myBeast3( 34, Synthescor ), myBeast4( 4, Stropie );

        me.party[0] = myBeast1;
        me.party[1] = myBeast2;
        me.party[2] = myBeast3;
        me.party[3] = myBeast4;

        REQUIRE( saveFile( me, 3 ) );

        REQUIRE( loadFile( me2, 3 ) );

        me2.printParty( );
    }
}



TEST_CASE( "Trainer Battle" )
{
    battle battle;
    trainer me, opponent;
    beast myBeast1( 40, Drakosis ), myBeast2( 41, Volcorage );
    beast oppBeast1( 40, Reptide ), oppBeast2( 46, Drakosis );

    me.party[0] = myBeast1;
    me.party[1] = myBeast2;

    opponent.party[0] = oppBeast1;
    opponent.party[1] = oppBeast2;

    battle.trainerBattle( me, opponent );

    REQUIRE( true );
}



TEST_CASE( "findEvolution" )
{
    beast testBeast;

    SECTION( "Level 5 Flacora" )
    {
        string ans = "Flacora";

        testBeast.setExp( 126 );
        getData( testBeast, Flacora );

        findEvolution( testBeast );

        REQUIRE( testBeast.nickName == ans );
    }
    SECTION( "Level 6 Stropie" )
    {
        string ans = "Stropie";

        testBeast.setExp( 220 );
        getData( testBeast, Stropie );

        findEvolution( testBeast );

        REQUIRE( testBeast.nickName == ans );
    }
    SECTION( "Level 19 Stropie" )
    {
        string ans = "Apolozard";

        testBeast.setExp( 6859 );
        getData( testBeast, Stropie );

        findEvolution( testBeast );

        REQUIRE( testBeast.nickName == ans );
    }
    SECTION( "Level 13 Apolozard" )
    {
        string ans = "Stropie";

        testBeast.setExp( 2197 );
        getData( testBeast, Apolozard );

        findEvolution( testBeast );

        REQUIRE( testBeast.nickName == ans );
    }
    SECTION( "Level 41 Stropie" )
    {
        string ans = "Reptide";

        testBeast.setExp( 68921 );
        getData( testBeast, Apolozard );

        findEvolution( testBeast );

        REQUIRE( testBeast.nickName == ans );
    }
    SECTION( "Level 2 Reptide" )
    {
        string ans = "Stropie";

        testBeast.setExp( 8 );
        getData( testBeast, Reptide );

        findEvolution( testBeast );

        REQUIRE( testBeast.nickName == ans );
    }
    SECTION( "Level 42 Apolozard" )
    {
        string ans = "Reptide";

        testBeast.setExp( 74088 );
        getData( testBeast, Apolozard );

        findEvolution( testBeast );

        REQUIRE( testBeast.nickName == ans );
    }

}



TEST_CASE( "generateRandBeast" )
{
    beast testBeast;
    trainer testTrainer;
    beast beast1, beast2, beast3;
    int i;
    random_device rand;

    for ( i = 0; i < 10; i++ )
    {
        beast1.setExp( rand( ) % 100000 );
        beast2.setExp( rand( ) % 100000 );
        beast3.setExp( rand( ) % 100000 );

        getData( beast1, Stropie );
        getData( beast2, Flacora );
        getData( beast3, Fotosin );

        testTrainer.party[0] = beast1;
        testTrainer.party[1] = beast2;
        testTrainer.party[2] = beast3;

        generateRandBeast( testTrainer, testBeast );

        printLine( );
        cout << endl;

        cout << "Beast 1 Exp/Level: " << beast1.getExp( ) << "/" << beast1.getLevel( ) << endl;
        cout << "Beast 2 Exp/Level: " << beast2.getExp( ) << "/" << beast2.getLevel( ) << endl;
        cout << "Beast 3 Exp/Level: " << beast3.getExp( ) << "/" << beast3.getLevel( ) << endl << endl;

        cout << "Generated beast: " << testBeast.nickName << "\nExp/Level: " << testBeast.getExp( ) << "/" << testBeast.getLevel( ) << endl;

        printLine( );
        cout << endl;
    }
}
*/