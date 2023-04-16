//******************************************************************************
/*! @file       test_command_parser.cpp
	@brief      Unit test for command parser
*/
//******************************************************************************

#include "test_toyRobot.hpp"
#include "command_parser.hpp"

#define ASSERT_ROBOT_INIT_STATE( robot ) assertRobot( robot, false, 0, 0, Direction::NORTH )

static void assertRobot( 
	Robot & robot,
	bool expected_isPlaced,
	int expected_x,
	int expected_y,
	Direction expected_direction )
{
	assert( robot.IsPlaced() == expected_isPlaced );
	assert( robot.GetCoordinate().GetX() == expected_x );
	assert( robot.GetCoordinate().GetY() == expected_y );
	assert( robot.GetDirection() == expected_direction );
}

static void test_placeCommand(
	string command,
	int expected_x,
	int expected_y,
	Direction expected_direction)
{
	Robot robot;
	Table table(5,5);
	CommandParser commandParser( robot, table );

	bool res = commandParser.parseCommand( command );
	assert( res );
	assertRobot( robot, true, expected_x, expected_y, expected_direction );
}

static void test_validPlaceCommands()
{
	test_placeCommand( "PLACE 0,0,SOUTH", 0, 0, Direction::SOUTH );
	test_placeCommand( "PLACE 4,4,NORTH", 4, 4, Direction::NORTH );
	test_placeCommand( "PLACE 0,4,WEST", 0, 4, Direction::WEST );
	test_placeCommand( "PLACE 4,0,EAST", 4, 0, Direction::EAST );
}

static void test_validMoveCommands()
{
	Robot robot;
	Table table(5,5);
	CommandParser commandParser( robot, table );
	bool res;

	// test initialization
	assert(commandParser.parseCommand( "PLACE 0,0,NORTH" ));
	assertRobot( robot, true, 0, 0, Direction::NORTH );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 0, 1, Direction::NORTH );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 0, 2, Direction::NORTH );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 0, 3, Direction::NORTH );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 0, 4, Direction::NORTH );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 0, 4, Direction::NORTH );

	// test initialization
	assert(commandParser.parseCommand( "PLACE 0,0,EAST" ));
	assertRobot( robot, true, 0, 0, Direction::EAST );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 1, 0, Direction::EAST );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 2, 0, Direction::EAST );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 3, 0, Direction::EAST );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 4, 0, Direction::EAST );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 4, 0, Direction::EAST );

	// test initialization
	assert(commandParser.parseCommand( "PLACE 4,0,WEST" ));
	assertRobot( robot, true, 4, 0, Direction::WEST );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 3, 0, Direction::WEST );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 2, 0, Direction::WEST );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 1, 0, Direction::WEST );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 0, 0, Direction::WEST );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 0, 0, Direction::WEST );

	// test initialization
	assert(commandParser.parseCommand( "PLACE 0,4,SOUTH" ));
	assertRobot( robot, true, 0, 4, Direction::SOUTH );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 0, 3, Direction::SOUTH );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 0, 2, Direction::SOUTH );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 0, 1, Direction::SOUTH );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 0, 0, Direction::SOUTH );

	res = commandParser.parseCommand( "MOVE" );
	assert( res );
	assertRobot( robot, true, 0, 0, Direction::SOUTH );
}

static void test_validLeft()
{
	Robot robot;
	Table table(5,5);
	CommandParser commandParser( robot, table );
	bool res;

	// test initialization
	assert(commandParser.parseCommand( "PLACE 0,0,NORTH" ));
	assertRobot( robot, true, 0, 0, Direction::NORTH );

	res = commandParser.parseCommand( "LEFT" );
	assert( res );
	assertRobot( robot, true, 0, 0, Direction::WEST );

	res = commandParser.parseCommand( "LEFT" );
	assert( res );
	assertRobot( robot, true, 0, 0, Direction::SOUTH );

	res = commandParser.parseCommand( "LEFT" );
	assert( res );
	assertRobot( robot, true, 0, 0, Direction::EAST );

	res = commandParser.parseCommand( "LEFT" );
	assert( res );
	assertRobot( robot, true, 0, 0, Direction::NORTH );
}

static void test_validRight()
{
	Robot robot;
	Table table(5,5);
	CommandParser commandParser( robot, table );
	bool res;

	// test initialization
	assert(commandParser.parseCommand( "PLACE 0,0,NORTH" ));
	assertRobot( robot, true, 0, 0, Direction::NORTH );

	res = commandParser.parseCommand( "RIGHT" );
	assert( res );
	assertRobot( robot, true, 0, 0, Direction::EAST );

	res = commandParser.parseCommand( "RIGHT" );
	assert( res );
	assertRobot( robot, true, 0, 0, Direction::SOUTH );

	res = commandParser.parseCommand( "RIGHT" );
	assert( res );
	assertRobot( robot, true, 0, 0, Direction::WEST );

	res = commandParser.parseCommand( "RIGHT" );
	assert( res );
	assertRobot( robot, true, 0, 0, Direction::NORTH );
}

static void test_validReport()
{
	Robot robot;
	Table table(5,5);
	CommandParser commandParser( robot, table );
	bool res;

	ostringstream strCout;
	streambuf* stream_buffer_cout;
    
	// test initialization
	assert(commandParser.parseCommand( "PLACE 0,0,NORTH" ));
	assertRobot( robot, true, 0, 0, Direction::NORTH );

	// redirect output
	stream_buffer_cout = cout.rdbuf();
	cout.rdbuf(strCout.rdbuf());

	strCout.clear();
	res = commandParser.parseCommand( "REPORT" );
	assert( res );
	assertRobot( robot, true, 0, 0, Direction::NORTH );
	assert( strCout.str().compare("Output : 0,0,NORTH\n") == 0 );

	// redirect output to original
	cout.rdbuf(stream_buffer_cout);
}

static void test_invalidCommands()
{
	Robot robot;
	Table table(5,5);
	CommandParser commandParser( robot, table );
	bool res;

	res = commandParser.parseCommand("");
	assert( res == false );
	ASSERT_ROBOT_INIT_STATE( robot );

	res = commandParser.parseCommand("PLACE 5,0,NORTH");
	assert( res );
	ASSERT_ROBOT_INIT_STATE( robot );

	res = commandParser.parseCommand("PLACE 0,5,NORTH");
	assert( res );
	ASSERT_ROBOT_INIT_STATE( robot );
}

int testCommandParser()
{
	TestHashMap testHashMap("Command Parser");
	testHashMap.AddTest("Test valid PLACE commands", test_validPlaceCommands);
	testHashMap.AddTest("Test valid MOVE commands", test_validMoveCommands);
	testHashMap.AddTest("Test valid LEFT commands", test_validLeft);
	testHashMap.AddTest("Test valid RIGHT commands", test_validRight);
	testHashMap.AddTest("Test valid REPORT commands", test_validReport);
	testHashMap.AddTest("Test valid invalid commands", test_invalidCommands);
	testHashMap.ExecuteTests();

	return testHashMap.GetTestCount();
}
