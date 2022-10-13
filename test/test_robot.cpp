//******************************************************************************
/*! @file       test_robot.cpp
	@brief      Unit test for robot
*/
//******************************************************************************

#include "gtest/gtest.h"
#include "robot.hpp"
#include "test_helper.h"

//******************************************************************************
//               Private type declaration
//******************************************************************************

/** Test move command class */
class CTestMoveCommand : public CCommand
{
public:
	/**
	* @brief Test move command constructor
	*/
    CTestMoveCommand()
    {
        SetMove(true);
    }
	/**
	* @brief Test move command deconstructor
	*/
    ~CTestMoveCommand(){}
};

/** Test right command class */
class CTestRightCommand : public CCommand
{
public:
	/**
	* @brief Test right command constructor
	*/
    CTestRightCommand()
    {
        SetRotate( CRotate::RIGHT );
    }
	/**
	* @brief Test right command deconstructor
	*/
    ~CTestRightCommand(){}
};

/** Test left command class */
class CTestLeftCommand : public CCommand
{
public:
	/**
	* @brief Test left command constructor
	*/
    CTestLeftCommand()
    {
        SetRotate( CRotate::LEFT );
    }
	/**
	* @brief Test left command deconstructor
	*/
    ~CTestLeftCommand(){}
};

//******************************************************************************
//               Private function declaration
//******************************************************************************

/*
* @brief Test helper to assert robot position
* @param robot
* @param x
* @param y
*/
void AssertRobotPosition(CRobot* const robot, int x, int y);

/*
* @brief Test helper to assert robot direction
* @param robot
* @param direction
*/
void AssertRobotDirection(CRobot* const robot, CDirection direction);

/*
* @brief Test helper to assert robot is in initial state
* @param robot
*/
void AssertRobotInInitState(CRobot* const robot);

//******************************************************************************
//               Private function definition
//******************************************************************************

void AssertRobotPosition(CRobot* const robot, int x, int y)
{
    stPosition position = robot->GetPosition();
    EXPECT_EQ(x, position.x);
    EXPECT_EQ(y, position.y);
}

void AssertRobotDirection(CRobot* const robot, CDirection direction)
{
    int expectedDirection = static_cast<int>(direction);
    int actualDirection = static_cast<int>(robot->GetDirection());
    EXPECT_EQ(expectedDirection, actualDirection);
}

void AssertRobotInInitState(CRobot* const robot)
{
    EXPECT_FALSE(robot->IsPlaced());
    AssertRobotDirection(robot, CDirection::NORTH);
    AssertRobotPosition(robot, INIT_X_POS, INIT_Y_POS);
}

//******************************************************************************
//               Test functions
//******************************************************************************

/*! @brief Test robot initialisation
*/
TEST( TestRobot, Test_RobotInitialisation )
{
    CTable table(5, 10);
    CRobot robot(&table);

    AssertRobotInInitState(&robot);
}

/*! @brief Test robot initialisation with NULL table throws exception
*/
TEST( TestRobot, Test_CreatingRobotExceptionForNullTable )
{
    bool exceptionThrown = false;

    try
    {
        CRobot robot(nullptr);
    }
    catch (RobotNullTableException& e)
    {
        exceptionThrown = true;
        EXPECT_EQUAL_CONST_CHAR_STRING( "Unable to create robot with NULL table", e.what() );
    }
    EXPECT_TRUE(exceptionThrown);
}

/*! @brief Test robot ignores non-PLACE command if not yet placed
*/
TEST( TestRobot, Test_RobotIgnoreNonPlaceCommandsIfNotYetPlaced )
{
    CTable table(5, 5);
    CRobot robot(&table);
    CTestMoveCommand m_moveCommand;
    CTestLeftCommand m_rotateLeftCommand;

    CCommandApplyResult result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::ROBOT_NOT_YET_PLACED),
        static_cast<int>(result));
    AssertRobotInInitState(&robot);

    result = robot.ApplyCommand(&m_rotateLeftCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::ROBOT_NOT_YET_PLACED),
        static_cast<int>(result));
    AssertRobotInInitState(&robot);
}

/*! @brief Test robot accepts PLACE command with valid position
*/
TEST( TestRobot, Test_RobotAcceptsPlaceCommandWithValidPosition)
{
    CTable table(5, 5);
    CRobot robot(&table);
    stPlacement placement;
    CCommand m_placeCommand;

    placement.position.x = 1;
    placement.position.y = 3;
    placement.direction = CDirection::NORTH;
    m_placeCommand.SetPlacement(placement);

    CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    EXPECT_TRUE(robot.IsPlaced());
    AssertRobotPosition(&robot, 1, 3);
}

/*! @brief Test robot can accept another PLACE command
*/
TEST( TestRobot, Test_RobotAcceptsAnotherPlaceCommandWithValidPosition)
{
    CTable table(5, 5);
    CRobot robot(&table);
    stPlacement placement;
    CCommand m_placeCommand;
    CTestMoveCommand m_moveCommand;

    placement.position.x = 1;
    placement.position.y = 3;
    placement.direction = CDirection::NORTH;
    m_placeCommand.SetPlacement(placement);

    CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    EXPECT_TRUE(robot.IsPlaced());
    AssertRobotPosition(&robot, 1, 3);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));

    placement.position.x = 3;
    placement.position.y = 1;
    placement.direction = CDirection::EAST;
    m_placeCommand.SetPlacement(placement);

    result = robot.ApplyCommand(&m_placeCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    EXPECT_TRUE(robot.IsPlaced());
    AssertRobotPosition(&robot, 3, 1);
}

/*! @brief Test robot rejects command with invalid position
*/
TEST( TestRobot, Test_RobotRejectsPlaceCommandWithInvalidPosition)
{
    CTable table(5, 5);
    CRobot robot(&table);
    stPlacement placement;
    CCommand m_placeCommand;

    placement.position.x = -1;
    placement.position.y = 3;
    placement.direction = CDirection::NORTH;
    m_placeCommand.SetPlacement(placement);

    CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::INVALID_PLACE),
        static_cast<int>(result));
    AssertRobotInInitState(&robot);
}

/*! @brief Test robot accepts command after being placed
*/
TEST( TestRobot, Test_RobotAcceptsCommandAfterBeingPlaced)
{
    CTable table(5, 5);
    CRobot robot(&table);
    stPlacement placement;
    CCommand m_placeCommand;
    CTestMoveCommand m_moveCommand;

    placement.position.x = 0;
    placement.position.y = 0;
    placement.direction = CDirection::NORTH;
    m_placeCommand.SetPlacement(placement);

    CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    EXPECT_TRUE(robot.IsPlaced());

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 1);
}

/*! @brief Test robot responds to rotate command after being placed
*/
TEST( TestRobot, Test_RobotRespondsCorrectlyToRotateCommandIfPlacedAlready)
{
    CTable table(5, 5);
    CRobot robot(&table);
    stPlacement placement;
    CCommand m_placeCommand;
    CTestLeftCommand m_rotateLeftCommand;
    CTestRightCommand m_rotateRightCommand;

    placement.position.x = 0;
    placement.position.y = 0;
    placement.direction = CDirection::NORTH;
    m_placeCommand.SetPlacement(placement);

    CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    EXPECT_TRUE(robot.IsPlaced());

    result = robot.ApplyCommand(&m_rotateLeftCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 0);
    AssertRobotDirection(&robot, CDirection::WEST);

    result = robot.ApplyCommand(&m_rotateLeftCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 0);
    AssertRobotDirection(&robot, CDirection::SOUTH);

    result = robot.ApplyCommand(&m_rotateLeftCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 0);
    AssertRobotDirection(&robot, CDirection::EAST);

    result = robot.ApplyCommand(&m_rotateLeftCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 0);
    AssertRobotDirection(&robot, CDirection::NORTH);

    result = robot.ApplyCommand(&m_rotateRightCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 0);
    AssertRobotDirection(&robot, CDirection::EAST);

    result = robot.ApplyCommand(&m_rotateRightCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 0);
    AssertRobotDirection(&robot, CDirection::SOUTH);

    result = robot.ApplyCommand(&m_rotateRightCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 0);
    AssertRobotDirection(&robot, CDirection::WEST);

    result = robot.ApplyCommand(&m_rotateRightCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 0);
    AssertRobotDirection(&robot, CDirection::NORTH);
}

/*! @brief Test robot responds to move command after being placed
*/
TEST( TestRobot, Test_RobotRespondsCorrectlyToMoveCommandIfPlacedAlready)
{
    CTable table(5, 5);
    CRobot robot(&table);
    stPlacement placement;
    CCommand m_placeCommand;
    CTestMoveCommand m_moveCommand;
    CTestRightCommand m_rotateRightCommand;
    CTestLeftCommand m_rotateLeftCommand;

    placement.position.x = 0;
    placement.position.y = 0;
    placement.direction = CDirection::NORTH;
    m_placeCommand.SetPlacement(placement);

    CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    EXPECT_TRUE(robot.IsPlaced());

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 1);
    AssertRobotDirection(&robot, CDirection::NORTH);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 2);
    AssertRobotDirection(&robot, CDirection::NORTH);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 3);
    AssertRobotDirection(&robot, CDirection::NORTH);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 4);
    AssertRobotDirection(&robot, CDirection::NORTH);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::IGNORE_FALL_OFF_MOVE),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 4);
    AssertRobotDirection(&robot, CDirection::NORTH);

    // turn right
    result = robot.ApplyCommand(&m_rotateRightCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 4);
    AssertRobotDirection(&robot, CDirection::EAST);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 1, 4);
    AssertRobotDirection(&robot, CDirection::EAST);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 2, 4);
    AssertRobotDirection(&robot, CDirection::EAST);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 3, 4);
    AssertRobotDirection(&robot, CDirection::EAST);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 4, 4);
    AssertRobotDirection(&robot, CDirection::EAST);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::IGNORE_FALL_OFF_MOVE),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 4, 4);
    AssertRobotDirection(&robot, CDirection::EAST);

    // turn left
    result = robot.ApplyCommand(&m_rotateLeftCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 4, 4);
    AssertRobotDirection(&robot, CDirection::NORTH);

    // turn left
    result = robot.ApplyCommand(&m_rotateLeftCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 4, 4);
    AssertRobotDirection(&robot, CDirection::WEST);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 3, 4);
    AssertRobotDirection(&robot, CDirection::WEST);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 2, 4);
    AssertRobotDirection(&robot, CDirection::WEST);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 1, 4);
    AssertRobotDirection(&robot, CDirection::WEST);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 4);
    AssertRobotDirection(&robot, CDirection::WEST);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::IGNORE_FALL_OFF_MOVE),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 4);
    AssertRobotDirection(&robot, CDirection::WEST);

    // turn left
    result = robot.ApplyCommand(&m_rotateLeftCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 4);
    AssertRobotDirection(&robot, CDirection::SOUTH);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 3);
    AssertRobotDirection(&robot, CDirection::SOUTH);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 2);
    AssertRobotDirection(&robot, CDirection::SOUTH);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 1);
    AssertRobotDirection(&robot, CDirection::SOUTH);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 0);
    AssertRobotDirection(&robot, CDirection::SOUTH);

    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::IGNORE_FALL_OFF_MOVE),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 0);
    AssertRobotDirection(&robot, CDirection::SOUTH);
}

/*! @brief Test robot test case 1
*/
TEST( TestRobot, Test_Robot_Place_0_0_North_Move)
{
    CTable table(5, 5);
    CRobot robot(&table);
    stPlacement placement;
    CCommand m_placeCommand;
    CTestMoveCommand m_moveCommand;

    placement.position.x = 0;
    placement.position.y = 0;
    placement.direction = CDirection::NORTH;
    m_placeCommand.SetPlacement(placement);

    // place
    CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    EXPECT_TRUE(robot.IsPlaced());

    // move
    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 1);
    AssertRobotDirection(&robot, CDirection::NORTH);
}

/*! @brief Test robot test case 2
*/
TEST( TestRobot, Test_Robot_Place_0_0_North_Left)
{
    CTable table(5, 5);
    CRobot robot(&table);
    stPlacement placement;
    CCommand m_placeCommand;
    CTestLeftCommand m_rotateLeftCommand;

    placement.position.x = 0;
    placement.position.y = 0;
    placement.direction = CDirection::NORTH;
    m_placeCommand.SetPlacement(placement);

    // place
    CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    EXPECT_TRUE(robot.IsPlaced());

    // left
    result = robot.ApplyCommand(&m_rotateLeftCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 0, 0);
    AssertRobotDirection(&robot, CDirection::WEST);
}

/*! @brief Test robot test case 3
*/
TEST( TestRobot, Test_Robot_Place_1_2_East_Move_Move_Left_Move)
{
    CTable table(5, 5);
    CRobot robot(&table);
    stPlacement placement;
    CCommand m_placeCommand;
    CTestMoveCommand m_moveCommand;
    CTestLeftCommand m_rotateLeftCommand;

    placement.position.x = 1;
    placement.position.y = 2;
    placement.direction = CDirection::EAST;
    m_placeCommand.SetPlacement(placement);

    // place
    CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    EXPECT_TRUE(robot.IsPlaced());

    // move
    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 2, 2);
    AssertRobotDirection(&robot, CDirection::EAST);

    // move
    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 3, 2);
    AssertRobotDirection(&robot, CDirection::EAST);

    // left
    result = robot.ApplyCommand(&m_rotateLeftCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 3, 2);
    AssertRobotDirection(&robot, CDirection::NORTH);

    // move
    result = robot.ApplyCommand(&m_moveCommand);
    EXPECT_EQ(
        static_cast<int>(CCommandApplyResult::OK),
        static_cast<int>(result));
    AssertRobotPosition(&robot, 3, 3);
    AssertRobotDirection(&robot, CDirection::NORTH);
}
