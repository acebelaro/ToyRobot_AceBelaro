//******************************************************************************
/*! @file       test_robot.cpp
	@brief      Unit test for robot
*/
//******************************************************************************

#include "test_toyRobot.hpp"
#include "robot.hpp"
#include <sstream>

#define ASSERT_ROBOT_INIT_STATE( robot )		assert(robot.IsPlaced() == false);\
												assert(robot.GetCoordinate().GetX() == 0 );\
												assert(robot.GetCoordinate().GetY() == 0 );\
												assert(robot.GetDirection() == Direction::NORTH )

static void test_robotInitialState()
{
	Robot robot;
	ASSERT_ROBOT_INIT_STATE(robot);
}

static void test_robotPlaceWithinBounds()
{
	Robot robot;
	Table table(5,5);
	Coordinate coordinate(1,2);
	Direction direction = Direction::SOUTH;
	RobotPosition robotPosition(coordinate,direction);

	robot.Place(robotPosition,table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::SOUTH );

	coordinate.SetX(3);
	coordinate.SetY(2);
	robotPosition.SetCoordinate(coordinate);
	direction = Direction::NORTH;
	robotPosition.SetDirection(direction);
	robot.Place(robotPosition,table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 3 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::NORTH );

	coordinate.SetX(0);
	coordinate.SetY(0);
	robotPosition.SetCoordinate(coordinate);
	direction = Direction::EAST;
	robotPosition.SetDirection(direction);
	robot.Place(robotPosition,table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 0 );
	assert(robot.GetCoordinate().GetY() == 0 );
	assert(robot.GetDirection() == Direction::EAST );

	coordinate.SetX(4);
	coordinate.SetY(1);
	robotPosition.SetCoordinate(coordinate);
	direction = Direction::WEST;
	robotPosition.SetDirection(direction);
	robot.Place(robotPosition,table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 4 );
	assert(robot.GetCoordinate().GetY() == 1);
	assert(robot.GetDirection() == Direction::WEST );
}

static void assert_robotPlaceOutsideBounds(int x,int y)
{
	Robot robot;
	Table table(5,5);
	Coordinate coordinate(x,y);
	Direction direction = Direction::SOUTH;
	RobotPosition robotPosition(coordinate,direction);
	ostringstream strCout;
	streambuf* stream_buffer_cout;

	// redirect output
	stream_buffer_cout = cout.rdbuf();
	cout.rdbuf(strCout.rdbuf());

	robot.Place(robotPosition,table);
	assert(robot.IsPlaced() == false);
	assert(robot.GetCoordinate().GetX() == 0);
	assert(robot.GetCoordinate().GetY() == 0 );
	assert(robot.GetDirection() == Direction::NORTH );
	assert( strCout.str().compare("Outside bounds!") == 0 );

	// redirect output to original
	cout.rdbuf(stream_buffer_cout);
}

static void test_robotPlaceOutsideBounds()
{
	assert_robotPlaceOutsideBounds(5,0);
	assert_robotPlaceOutsideBounds(0,5);
	assert_robotPlaceOutsideBounds(5,5);
	assert_robotPlaceOutsideBounds(-1,0);
	assert_robotPlaceOutsideBounds(0,-1);
	assert_robotPlaceOutsideBounds(-1,-1);
}

static void test_rotateLeftWhenRobotIsPlaced()
{
	Robot robot;
	Table table(5,5);
	Coordinate coordinate(1,2);
	RobotPosition robotPosition(coordinate,Direction::SOUTH);

	robot.Place(robotPosition,table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::SOUTH );

	robot.RotateLeft();
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::EAST );

	robot.RotateLeft();
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::NORTH );

	robot.RotateLeft();
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::WEST );

	robot.RotateLeft();
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::SOUTH );
}

static void test_rotateLeftWhenRobotIsNotYetPlaced()
{
	Robot robot;
	ostringstream strCout;
	streambuf* stream_buffer_cout;

	// redirect output
	stream_buffer_cout = cout.rdbuf();
	cout.rdbuf(strCout.rdbuf());

	strCout.clear();
	robot.RotateLeft();
	ASSERT_ROBOT_INIT_STATE(robot);
	assert( strCout.str().compare("Robot not yet placed!") == 0 );

	// redirect output to original
	cout.rdbuf(stream_buffer_cout);
}

static void test_rotateRightWhenRobotIsPlaced()
{
	Robot robot;
	Table table(5,5);
	Coordinate coordinate(1,2);
	RobotPosition robotPosition(coordinate,Direction::SOUTH);

	robot.Place(robotPosition,table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::SOUTH );

	robot.RotateRight();
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::WEST );

	robot.RotateRight();
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::NORTH );

	robot.RotateRight();
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::EAST );

	robot.RotateRight();
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::SOUTH );
}

static void test_rotateRightWhenRobotIsNotYetPlaced()
{
	Robot robot;
	ostringstream strCout;
	streambuf* stream_buffer_cout;

	// redirect output
	stream_buffer_cout = cout.rdbuf();
	cout.rdbuf(strCout.rdbuf());

	robot.RotateRight();
	ASSERT_ROBOT_INIT_STATE(robot);
	assert( strCout.str().compare("Robot not yet placed!") == 0 );

	// redirect output to original
	cout.rdbuf(stream_buffer_cout);
}

static void test_moveToSouthWhenRobotIsPlaced()
{
	Robot robot;
	Table table(5,5);
	Coordinate coordinate(1,2);
	RobotPosition robotPosition(coordinate,Direction::SOUTH);

	robot.Place(robotPosition,table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::SOUTH );

	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 1 );
	assert(robot.GetDirection() == Direction::SOUTH );

	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 0 );
	assert(robot.GetDirection() == Direction::SOUTH );
}

static void test_moveToNorthWhenRobotIsPlaced()
{
	Robot robot;
	Table table(5,5);
	Coordinate coordinate(1,2);
	RobotPosition robotPosition(coordinate,Direction::NORTH);

	robot.Place(robotPosition,table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::NORTH );

	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 3 );
	assert(robot.GetDirection() == Direction::NORTH );

	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 4 );
	assert(robot.GetDirection() == Direction::NORTH );
}

static void test_moveToEastWhenRobotIsPlaced()
{
	Robot robot;
	Table table(5,5);
	Coordinate coordinate(1,2);
	RobotPosition robotPosition(coordinate,Direction::EAST);

	robot.Place(robotPosition,table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::EAST );

	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 2 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::EAST );

	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 3 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::EAST );

	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 4 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::EAST );
}

static void test_moveToWestWhenRobotIsPlaced()
{
	Robot robot;
	Table table(5,5);
	Coordinate coordinate(4,2);
	RobotPosition robotPosition(coordinate,Direction::WEST);

	robot.Place(robotPosition,table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 4 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::WEST );

	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 3 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::WEST );

	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 2 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::WEST );

	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::WEST );

	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 0 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::WEST );
}

static void assert_moveWhenRobotIsPlacedAndFallingOff(int x,int y,Direction direction)
{
	Robot robot;
	Table table(5,5);
	Coordinate coordinate(x,y);
	RobotPosition robotPosition(coordinate,direction);
	ostringstream strCout;
	streambuf* stream_buffer_cout;

	// redirect output
	stream_buffer_cout = cout.rdbuf();
	cout.rdbuf(strCout.rdbuf());

	// test falling off to NORTH side
	robot.Place(robotPosition,table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == x );
	assert(robot.GetCoordinate().GetY() == y );
	assert(robot.GetDirection() == direction );
	strCout.clear();
	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == x );
	assert(robot.GetCoordinate().GetY() == y );
	assert(robot.GetDirection() == direction );
	assert( strCout.str().compare("Robot falling off!") == 0 );

	// redirect output to original
	cout.rdbuf(stream_buffer_cout);
}

static void test_moveWhenRobotIsPlacedAndFallingOff()
{
	assert_moveWhenRobotIsPlacedAndFallingOff(0,4,Direction::NORTH);
	assert_moveWhenRobotIsPlacedAndFallingOff(4,0,Direction::SOUTH);
	assert_moveWhenRobotIsPlacedAndFallingOff(4,0,Direction::EAST);
	assert_moveWhenRobotIsPlacedAndFallingOff(0,4,Direction::WEST);
}

static void test_moveWhenRobotIsNotYetPlaced()
{
	Robot robot;
	Table table(5,5);
	ostringstream strCout;
	streambuf* stream_buffer_cout;

	// redirect output
	stream_buffer_cout = cout.rdbuf();
	cout.rdbuf(strCout.rdbuf());

	robot.Move(table);
	ASSERT_ROBOT_INIT_STATE(robot);

	// redirect output to original
	cout.rdbuf(stream_buffer_cout);
}

static void test_robotReportWhenRobotIsPlaced()
{
	Robot robot;
	Table table(5,5);
	Coordinate coordinate(1,2);
	Direction direction = Direction::SOUTH;
	RobotPosition robotPosition(coordinate,direction);

	robot.Place(robotPosition,table);
	assert( robot.Report().compare("1,2,SOUTH") == 0 );

	coordinate.SetX(3);
	coordinate.SetY(2);
	robotPosition.SetCoordinate(coordinate);
	direction = Direction::NORTH;
	robotPosition.SetDirection(direction);
	robot.Place(robotPosition,table);
	assert( robot.Report().compare("3,2,NORTH") == 0 );

	coordinate.SetX(0);
	coordinate.SetY(0);
	robotPosition.SetCoordinate(coordinate);
	direction = Direction::EAST;
	robotPosition.SetDirection(direction);
	robot.Place(robotPosition,table);
	assert( robot.Report().compare("0,0,EAST") == 0 );

	coordinate.SetX(4);
	coordinate.SetY(1);
	robotPosition.SetCoordinate(coordinate);
	direction = Direction::WEST;
	robotPosition.SetDirection(direction);
	robot.Place(robotPosition,table);
	assert( robot.Report().compare("4,1,WEST") == 0 );
}

static void test_robotReportWhenRobotIsNotYetPlaced()
{
	Robot robot;
	ostringstream strCout;
	streambuf* stream_buffer_cout;

	// redirect output
	stream_buffer_cout = cout.rdbuf();
	cout.rdbuf(strCout.rdbuf());

	assert( robot.Report().compare("") == 0 );
	assert( strCout.str().compare("Robot not yet placed!") == 0 );

	// redirect output to original
	cout.rdbuf(stream_buffer_cout);
}

int testRobot()
{
	TestHashMap testHashMap("Robot");
	testHashMap.AddTest("Test robot initial state",test_robotInitialState);
	testHashMap.AddTest("Test robot place within bounds",test_robotPlaceWithinBounds);
	testHashMap.AddTest("Test robot place outside bounds",test_robotPlaceOutsideBounds);
	testHashMap.AddTest("Test rotate left when robot is placed",test_rotateLeftWhenRobotIsPlaced);
	testHashMap.AddTest("Test rotate left when robot is not yet placed",test_rotateLeftWhenRobotIsNotYetPlaced);
	testHashMap.AddTest("Test rotate right when robot is placed",test_rotateRightWhenRobotIsPlaced);
	testHashMap.AddTest("Test rotate right when robot is not yet placed",test_rotateRightWhenRobotIsNotYetPlaced);
	testHashMap.AddTest("Test move to south when robot is placed",test_moveToSouthWhenRobotIsPlaced);
	testHashMap.AddTest("Test move to north when robot is placed",test_moveToNorthWhenRobotIsPlaced);
	testHashMap.AddTest("Test move to east when robot is placed",test_moveToEastWhenRobotIsPlaced);
	testHashMap.AddTest("Test move to west when robot is placed",test_moveToWestWhenRobotIsPlaced);
	testHashMap.AddTest("Test move when robot is placed and falling off",test_moveWhenRobotIsPlacedAndFallingOff);
	testHashMap.AddTest("Test move when robot is not yet placed",test_moveWhenRobotIsNotYetPlaced);
	testHashMap.AddTest("Test report when robot is placed",test_robotReportWhenRobotIsPlaced);
	testHashMap.AddTest("Test report when robot is not yet placed",test_robotReportWhenRobotIsNotYetPlaced);
	testHashMap.ExecuteTests();

	return testHashMap.GetTestCount();
}