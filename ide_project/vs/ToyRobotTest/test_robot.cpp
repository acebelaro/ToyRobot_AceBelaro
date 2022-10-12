#include "CppUnitTest.h"
#include "robot.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ToyRobotTest
{
	TEST_CLASS(RobotTest)
	{
	public:
		RobotTest() {
			m_moveCommand.SetMove(true);
			m_rotateLeftCommand.SetRotate(CRotate::LEFT);
			m_rotateRightCommand.SetRotate(CRotate::RIGHT);
		}

		~RobotTest() {

		}

	private:
		CCommand m_placeCommand; // set accordingly per test
		CCommand m_moveCommand;
		CCommand m_rotateLeftCommand;
		CCommand m_rotateRightCommand;

		void AssertRobotPosition(CRobot* const robot, int x, int y)
		{
			stPosition position = robot->GetPosition();
			Assert::AreEqual(x, position.x);
			Assert::AreEqual(y, position.y);
		}

		void AssertRobotDirection(CRobot* const robot, CDirection direction)
		{
			int expectedDirection = static_cast<int>(direction);
			int actualDirection = static_cast<int>(robot->GetDirection());
			Assert::AreEqual(expectedDirection, actualDirection);
		}

		void AssertRobotInInitState(CRobot* const robot)
		{
			Assert::IsFalse(robot->IsPlaced());
			AssertRobotDirection(robot, CDirection::NORTH);
			AssertRobotPosition(robot, INIT_X_POS, INIT_Y_POS);
		}

	public:

		TEST_METHOD(Test_RobotInitialisation)
		{
			CTable table(5, 10);
			CRobot robot(&table);

			AssertRobotInInitState(&robot);
		}

		TEST_METHOD(Test_CreatingRobotExceptionForNullTable)
		{
			bool exceptionThrown = false;

			try
			{
				CRobot robot(nullptr);
			}
			catch (RobotNullTableException& e)
			{
				exceptionThrown = true;
				Assert::AreEqual("Unable to create robot with NULL table", e.what());
			}
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(Test_RobotIgnoreNonPlaceCommandsIfNotYetPlaced)
		{
			CTable table(5, 5);
			CRobot robot(&table);

			CCommandApplyResult result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::ROBOT_NOT_YET_PLACED),
				static_cast<int>(result));
			AssertRobotInInitState(&robot);

			result = robot.ApplyCommand(&m_rotateLeftCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::ROBOT_NOT_YET_PLACED),
				static_cast<int>(result));
			AssertRobotInInitState(&robot);
		}

		TEST_METHOD(Test_RobotAcceptsPlaceCommandWithValidPosition)
		{
			CTable table(5, 5);
			CRobot robot(&table);
			stPlacement placement;

			placement.position.x = 1;
			placement.position.y = 3;
			placement.direction = CDirection::NORTH;
			m_placeCommand.SetPlacement(placement);

			CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			Assert::IsTrue(robot.IsPlaced());
			AssertRobotPosition(&robot, 1, 3);
		}

		TEST_METHOD(Test_RobotAcceptsAnotherPlaceCommandWithValidPosition)
		{
			CTable table(5, 5);
			CRobot robot(&table);
			stPlacement placement;

			placement.position.x = 1;
			placement.position.y = 3;
			placement.direction = CDirection::NORTH;
			m_placeCommand.SetPlacement(placement);

			CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			Assert::IsTrue(robot.IsPlaced());
			AssertRobotPosition(&robot, 1, 3);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));

			placement.position.x = 3;
			placement.position.y = 1;
			placement.direction = CDirection::EAST;
			m_placeCommand.SetPlacement(placement);

			result = robot.ApplyCommand(&m_placeCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			Assert::IsTrue(robot.IsPlaced());
			AssertRobotPosition(&robot, 3, 1);
		}

		TEST_METHOD(Test_RobotRejectsPlaceCommandWithInvalidPosition)
		{
			CTable table(5, 5);
			CRobot robot(&table);
			stPlacement placement;

			placement.position.x = -1;
			placement.position.y = 3;
			placement.direction = CDirection::NORTH;
			m_placeCommand.SetPlacement(placement);

			CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::INVALID_PLACE),
				static_cast<int>(result));
			AssertRobotInInitState(&robot);
		}

		TEST_METHOD(Test_RobotAcceptsCommandAfterBeingPlaced)
		{
			CTable table(5, 5);
			CRobot robot(&table);
			stPlacement placement;

			placement.position.x = 0;
			placement.position.y = 0;
			placement.direction = CDirection::NORTH;
			m_placeCommand.SetPlacement(placement);

			CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			Assert::IsTrue(robot.IsPlaced());

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 1);
		}

		TEST_METHOD(Test_RobotRespondsCorrectlyToRotateCommandIfPlacedAlready)
		{
			CTable table(5, 5);
			CRobot robot(&table);
			stPlacement placement;

			placement.position.x = 0;
			placement.position.y = 0;
			placement.direction = CDirection::NORTH;
			m_placeCommand.SetPlacement(placement);

			CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			Assert::IsTrue(robot.IsPlaced());

			result = robot.ApplyCommand(&m_rotateLeftCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 0);
			AssertRobotDirection(&robot, CDirection::WEST);

			result = robot.ApplyCommand(&m_rotateLeftCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 0);
			AssertRobotDirection(&robot, CDirection::SOUTH);

			result = robot.ApplyCommand(&m_rotateLeftCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 0);
			AssertRobotDirection(&robot, CDirection::EAST);

			result = robot.ApplyCommand(&m_rotateLeftCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 0);
			AssertRobotDirection(&robot, CDirection::NORTH);

			result = robot.ApplyCommand(&m_rotateRightCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 0);
			AssertRobotDirection(&robot, CDirection::EAST);

			result = robot.ApplyCommand(&m_rotateRightCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 0);
			AssertRobotDirection(&robot, CDirection::SOUTH);

			result = robot.ApplyCommand(&m_rotateRightCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 0);
			AssertRobotDirection(&robot, CDirection::WEST);

			result = robot.ApplyCommand(&m_rotateRightCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 0);
			AssertRobotDirection(&robot, CDirection::NORTH);
		}

		TEST_METHOD(Test_RobotRespondsCorrectlyToMoveCommandIfPlacedAlready)
		{
			CTable table(5, 5);
			CRobot robot(&table);
			stPlacement placement;

			placement.position.x = 0;
			placement.position.y = 0;
			placement.direction = CDirection::NORTH;
			m_placeCommand.SetPlacement(placement);

			CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			Assert::IsTrue(robot.IsPlaced());

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 1);
			AssertRobotDirection(&robot, CDirection::NORTH);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 2);
			AssertRobotDirection(&robot, CDirection::NORTH);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 3);
			AssertRobotDirection(&robot, CDirection::NORTH);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 4);
			AssertRobotDirection(&robot, CDirection::NORTH);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::IGNORE_FALL_OFF_MOVE),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 4);
			AssertRobotDirection(&robot, CDirection::NORTH);

			// turn right
			result = robot.ApplyCommand(&m_rotateRightCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 4);
			AssertRobotDirection(&robot, CDirection::EAST);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 1, 4);
			AssertRobotDirection(&robot, CDirection::EAST);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 2, 4);
			AssertRobotDirection(&robot, CDirection::EAST);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 3, 4);
			AssertRobotDirection(&robot, CDirection::EAST);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 4, 4);
			AssertRobotDirection(&robot, CDirection::EAST);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::IGNORE_FALL_OFF_MOVE),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 4, 4);
			AssertRobotDirection(&robot, CDirection::EAST);

			// turn left
			result = robot.ApplyCommand(&m_rotateLeftCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 4, 4);
			AssertRobotDirection(&robot, CDirection::NORTH);

			// turn left
			result = robot.ApplyCommand(&m_rotateLeftCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 4, 4);
			AssertRobotDirection(&robot, CDirection::WEST);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 3, 4);
			AssertRobotDirection(&robot, CDirection::WEST);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 2, 4);
			AssertRobotDirection(&robot, CDirection::WEST);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 1, 4);
			AssertRobotDirection(&robot, CDirection::WEST);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 4);
			AssertRobotDirection(&robot, CDirection::WEST);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::IGNORE_FALL_OFF_MOVE),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 4);
			AssertRobotDirection(&robot, CDirection::WEST);

			// turn left
			result = robot.ApplyCommand(&m_rotateLeftCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 4);
			AssertRobotDirection(&robot, CDirection::SOUTH);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 3);
			AssertRobotDirection(&robot, CDirection::SOUTH);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 2);
			AssertRobotDirection(&robot, CDirection::SOUTH);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 1);
			AssertRobotDirection(&robot, CDirection::SOUTH);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 0);
			AssertRobotDirection(&robot, CDirection::SOUTH);

			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::IGNORE_FALL_OFF_MOVE),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 0);
			AssertRobotDirection(&robot, CDirection::SOUTH);
		}

		TEST_METHOD(Test_Robot_Place_0_0_North_Move)
		{
			CTable table(5, 5);
			CRobot robot(&table);
			stPlacement placement;

			placement.position.x = 0;
			placement.position.y = 0;
			placement.direction = CDirection::NORTH;
			m_placeCommand.SetPlacement(placement);

			// place
			CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			Assert::IsTrue(robot.IsPlaced());

			// move
			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 1);
			AssertRobotDirection(&robot, CDirection::NORTH);
		}

		TEST_METHOD(Test_Robot_Place_0_0_North_Left)
		{
			CTable table(5, 5);
			CRobot robot(&table);
			stPlacement placement;

			placement.position.x = 0;
			placement.position.y = 0;
			placement.direction = CDirection::NORTH;
			m_placeCommand.SetPlacement(placement);

			// place
			CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			Assert::IsTrue(robot.IsPlaced());

			// left
			result = robot.ApplyCommand(&m_rotateLeftCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 0, 0);
			AssertRobotDirection(&robot, CDirection::WEST);
		}

		TEST_METHOD(Test_Robot_Place_1_2_East_Move_Move_Left_Move)
		{
			CTable table(5, 5);
			CRobot robot(&table);
			stPlacement placement;

			placement.position.x = 1;
			placement.position.y = 2;
			placement.direction = CDirection::EAST;
			m_placeCommand.SetPlacement(placement);

			// place
			CCommandApplyResult result = robot.ApplyCommand(&m_placeCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			Assert::IsTrue(robot.IsPlaced());

			// move
			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 2, 2);
			AssertRobotDirection(&robot, CDirection::EAST);

			// move
			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 3, 2);
			AssertRobotDirection(&robot, CDirection::EAST);

			// left
			result = robot.ApplyCommand(&m_rotateLeftCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 3, 2);
			AssertRobotDirection(&robot, CDirection::NORTH);

			// move
			result = robot.ApplyCommand(&m_moveCommand);
			Assert::AreEqual(
				static_cast<int>(CCommandApplyResult::OK),
				static_cast<int>(result));
			AssertRobotPosition(&robot, 3, 3);
			AssertRobotDirection(&robot, CDirection::NORTH);
		}
	};
}
