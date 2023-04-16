//******************************************************************************
/*! @file       test_direction.cpp
	@brief      Unit test for direction
*/
//******************************************************************************

#include "test_toyRobot.hpp"
#include "direction.hpp"

static void test_StringToDirection()
{
	Direction direction;

	direction = StringToDirection("NORTH");
	assert( direction == Direction::NORTH );

	direction = StringToDirection("EAST");
	assert( direction == Direction::EAST );

	direction = StringToDirection("SOUTH");
	assert( direction == Direction::SOUTH );

	direction = StringToDirection("WEST");
	assert( direction == Direction::WEST );

	direction = StringToDirection("");
	assert( direction == Direction::NORTH ); // default
}

static void test_DirectionToString()
{
	const char* direction;

	direction = DirectionToString(Direction::NORTH);
	assert( string(direction).compare("NORTH") == 0 );

	direction = DirectionToString(Direction::EAST);
	assert( string(direction).compare("EAST") == 0 );

	direction = DirectionToString(Direction::SOUTH);
	assert( string(direction).compare("SOUTH") == 0 );

	direction = DirectionToString(Direction::WEST);
	assert( string(direction).compare("WEST") == 0 );
}

int testDirection()
{
	TestHashMap testHashMap("Direction");
	testHashMap.AddTest("Test string to direction conversion",test_StringToDirection);
	testHashMap.AddTest("Test direction to string conversion",test_DirectionToString);
	testHashMap.ExecuteTests();

	return testHashMap.GetTestCount();
}
