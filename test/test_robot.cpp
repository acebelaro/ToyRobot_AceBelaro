//******************************************************************************
/*! @file       test_robot.cpp
	@brief      Unit test for robot
*/
//******************************************************************************

#include "test_toyRobot.hpp"
#include "robot.hpp"

static void test_robotInitialState()
{
	Robot robot;

	assert(robot.IsPlaced() == false);
	assert(robot.GetCoordinate().GetX() == 0 );
	assert(robot.GetCoordinate().GetY() == 0 );
	assert(robot.GetDirection() == Direction::NORTH );
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

static void test_robotPlaceOutsideBounds()
{
	Robot robot;
	Table table(5,5);
	Coordinate coordinate(5,5);
	Direction direction = Direction::SOUTH;
	RobotPosition robotPosition(coordinate,direction);

	robot.Place(robotPosition,table);
	assert(robot.IsPlaced() == false);
	assert(robot.GetCoordinate().GetX() == 0);
	assert(robot.GetCoordinate().GetY() == 0 );
	assert(robot.GetDirection() == Direction::NORTH );

	coordinate.SetX(5);
	coordinate.SetY(0);
	robotPosition.SetCoordinate(coordinate);
	direction = Direction::WEST;
	robotPosition.SetDirection(direction);
	robot.Place(robotPosition,table);
	assert(robot.IsPlaced() == false);
	assert(robot.GetCoordinate().GetX() == 0);
	assert(robot.GetCoordinate().GetY() == 0 );
	assert(robot.GetDirection() == Direction::NORTH );

	coordinate.SetX(0);
	coordinate.SetY(5);
	robotPosition.SetCoordinate(coordinate);
	direction = Direction::WEST;
	robotPosition.SetDirection(direction);
	robot.Place(robotPosition,table);
	assert(robot.IsPlaced() == false);
	assert(robot.GetCoordinate().GetX() == 0);
	assert(robot.GetCoordinate().GetY() == 0 );
	assert(robot.GetDirection() == Direction::NORTH );

	coordinate.SetX(-1);
	coordinate.SetY(-1);
	robotPosition.SetCoordinate(coordinate);
	direction = Direction::WEST;
	robotPosition.SetDirection(direction);
	robot.Place(robotPosition,table);
	assert(robot.IsPlaced() == false);
	assert(robot.GetCoordinate().GetX() == 0);
	assert(robot.GetCoordinate().GetY() == 0 );
	assert(robot.GetDirection() == Direction::NORTH );

	coordinate.SetX(0);
	coordinate.SetY(-1);
	robotPosition.SetCoordinate(coordinate);
	direction = Direction::WEST;
	robotPosition.SetDirection(direction);
	robot.Place(robotPosition,table);
	assert(robot.IsPlaced() == false);
	assert(robot.GetCoordinate().GetX() == 0);
	assert(robot.GetCoordinate().GetY() == 0 );
	assert(robot.GetDirection() == Direction::NORTH );

	coordinate.SetX(-1);
	coordinate.SetY(0);
	robotPosition.SetCoordinate(coordinate);
	direction = Direction::WEST;
	robotPosition.SetDirection(direction);
	robot.Place(robotPosition,table);
	assert(robot.IsPlaced() == false);
	assert(robot.GetCoordinate().GetX() == 0);
	assert(robot.GetCoordinate().GetY() == 0 );
	assert(robot.GetDirection() == Direction::NORTH );
}

static void test_robotRotateLeft()
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

static void test_robotRotateRight()
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

static void test_robotMoveSouth()
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

	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 0 );
	assert(robot.GetDirection() == Direction::SOUTH );
}

static void test_robotMoveNorth()
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

	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 1 );
	assert(robot.GetCoordinate().GetY() == 4 );
	assert(robot.GetDirection() == Direction::NORTH );
}

static void test_robotMoveEast()
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

	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 4 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::EAST );
}

static void test_robotMoveWest()
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

	robot.Move(table);
	assert(robot.IsPlaced());
	assert(robot.GetCoordinate().GetX() == 0 );
	assert(robot.GetCoordinate().GetY() == 2 );
	assert(robot.GetDirection() == Direction::WEST );
}

static void test_robotReport()
{
	Robot robot;
	Table table(5,5);
	Coordinate coordinate(1,2);
	Direction direction = Direction::SOUTH;
	RobotPosition robotPosition(coordinate,direction);

	assert( robot.Report().compare("Robot not yet placed") == 0 );

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

int testRobot()
{
	TestHashMap testHashMap("Robot");
	testHashMap.AddTest("Test robot initial state",test_robotInitialState);
	testHashMap.AddTest("Test robot place within bounds",test_robotPlaceWithinBounds);
	testHashMap.AddTest("Test robot place outside bounds",test_robotPlaceOutsideBounds);
	testHashMap.AddTest("Test robot rotate left",test_robotRotateLeft);
	testHashMap.AddTest("Test robot rotate right",test_robotRotateRight);
	testHashMap.AddTest("Test robot rotate move south",test_robotMoveSouth);
	testHashMap.AddTest("Test robot rotate move north",test_robotMoveNorth);
	testHashMap.AddTest("Test robot rotate move east",test_robotMoveEast);
	testHashMap.AddTest("Test robot rotate move west",test_robotMoveWest);
	testHashMap.AddTest("Test robot rotate report",test_robotReport);
	testHashMap.ExecuteTests();

	return testHashMap.GetTestCount();
}