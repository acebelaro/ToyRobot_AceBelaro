//******************************************************************************
/*! @file       test_command_parser.cpp
	@brief      Unit test for command parser
*/
//******************************************************************************

#include <sstream>
#include <typeinfo>

#include "test_toyRobot.hpp"
#include "command_parser.hpp"
#include "place_command.hpp"
#include "move_command.hpp"
#include "rotate_command.hpp"
#include "report_command.hpp"

#define ASSERT_COMMAND_TYPE(uptr,type) assert( string(typeid(*uptr).name()).compare(string(typeid(type).name())) == 0 )

#define CAST_UPTR_COMMAND_TO_TYPE(obj,type) ((type*)obj.get())

static void test_placeCommand(
	string command,
	int expected_x,
	int expected_y,
	Direction expected_direction)
{
	UPTR_COMMAND cmd;
	CommandParser commandParser;

	bool res = commandParser.parseCommand(command, cmd);
	assert( res );
	assert( cmd != nullptr );
	ASSERT_COMMAND_TYPE(cmd, PlaceCommand);

	// assert place command parameters
	auto pCmd = CAST_UPTR_COMMAND_TO_TYPE(cmd,PlaceCommand);
	RobotPosition roboPosition = pCmd->GetRobotPosition();
	assert( expected_x == roboPosition.GetCoordinate().GetX() );
	assert( expected_y == roboPosition.GetCoordinate().GetY() );
	assert( expected_direction == roboPosition.GetDirection() );
}

static void test_validPlaceCommandsWithCoordinatesWithinBounds()
{
	test_placeCommand( "PLACE 0,0,SOUTH", 0, 0, Direction::SOUTH );
	test_placeCommand( "PLACE 4,4,NORTH", 4, 4, Direction::NORTH );
	test_placeCommand( "PLACE 0,4,WEST", 0, 4, Direction::WEST );
	test_placeCommand( "PLACE 4,0,EAST", 4, 0, Direction::EAST );
}

static void test_validPlaceCommandsWithInvalidParameters()
{
	UPTR_COMMAND cmd;
	CommandParser commandParser;
	bool res;

	res = commandParser.parseCommand("", cmd);
	assert( res == false );
	assert( cmd == nullptr );

	res = commandParser.parseCommand("PLACE x,0,NORTH", cmd);
	assert( res == false );
	assert( cmd == nullptr );

	res = commandParser.parseCommand("PLACE 0,x,NORTH", cmd);
	assert( res == false );
	assert( cmd == nullptr );

	res = commandParser.parseCommand("PLACE 0,0,NORTH?", cmd);
	assert( res == false );
	assert( cmd == nullptr );
}

static void test_validMoveCommands()
{
	UPTR_COMMAND cmd;
	CommandParser commandParser;
	bool res;

	res = commandParser.parseCommand("MOVE", cmd);
	assert( res );
	assert( cmd != nullptr );
	ASSERT_COMMAND_TYPE(cmd, MoveCommand);
}

static void test_validLeft()
{
	UPTR_COMMAND cmd;
	CommandParser commandParser;
	bool res;

	res = commandParser.parseCommand("LEFT", cmd);
	assert( res );
	assert( cmd != nullptr );
	ASSERT_COMMAND_TYPE(cmd, RotateCommand);

	// assert rotate command parameters
	auto pCmd = CAST_UPTR_COMMAND_TO_TYPE(cmd,RotateCommand);
	assert( Rotate::LEFT == pCmd->GetRotate() );
}

static void test_validRight()
{
	UPTR_COMMAND cmd;
	CommandParser commandParser;
	bool res;

	res = commandParser.parseCommand("RIGHT", cmd);
	assert( res );
	assert( cmd != nullptr );
	ASSERT_COMMAND_TYPE(cmd, RotateCommand);

	// assert rotate command parameters
	auto pCmd = CAST_UPTR_COMMAND_TO_TYPE(cmd,RotateCommand);
	assert( Rotate::RIGHT == pCmd->GetRotate() );
}

static void test_validReport()
{
	UPTR_COMMAND cmd;
	CommandParser commandParser;
	bool res;

	res = commandParser.parseCommand("REPORT", cmd);
	assert( res );
	assert( cmd != nullptr );
	ASSERT_COMMAND_TYPE(cmd, ReportCommand);
}

int testCommandParser()
{
	TestHashMap testHashMap("Command Parser");
	testHashMap.AddTest("Test valid PLACE commands with coordinates within bounds", test_validPlaceCommandsWithCoordinatesWithinBounds);
	testHashMap.AddTest("Test valid PLACE commands invalid parameters", test_validPlaceCommandsWithInvalidParameters);
	testHashMap.AddTest("Test valid MOVE commands and within founds", test_validMoveCommands);
	testHashMap.AddTest("Test valid LEFT commands", test_validLeft);
	testHashMap.AddTest("Test valid RIGHT commands", test_validRight);
	testHashMap.AddTest("Test valid REPORT commands", test_validReport);
	testHashMap.ExecuteTests();

	return testHashMap.GetTestCount();
}
