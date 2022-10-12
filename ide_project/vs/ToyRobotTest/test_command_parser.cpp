#include "CppUnitTest.h"
#include "command_parser.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ToyRobotTest
{
	TEST_CLASS(CommandParserTest)
	{
	private:

		void AssertPlacement(CCommand* command, int x, int y, CDirection direction) {
			stPlacement placement = command->GetPlacement();
			Assert::AreEqual(static_cast<int>(direction),
				static_cast<int>(placement.direction));
			Assert::AreEqual(x, placement.position.x);
			Assert::AreEqual(y, placement.position.y);
		}

		void AssertPlacementIsInitState(CCommand* command) {
			AssertPlacement(command, INIT_X_POS, INIT_Y_POS, INIT_PLACEMENT_DIRECTION);
		}

		void AssertParserThrowsInvalidCommandException(std::string str, std::string commandName)
		{
			bool exceptionThrown = false;
			try
			{
				CCommandParser commandParser;
				CCommand* command;

				command = commandParser.ParseCommand(str);
			}
			catch (InvalidCommandException& e)
			{
				exceptionThrown = true;
				Assert::AreEqual(std::string(e.what()), std::string("Invalid command : ") + commandName);
			}
			Assert::IsTrue(exceptionThrown);
		}

		void AssertParserThrowsInvalidInvalidParameterCountException(std::string str, std::string parameters)
		{
			bool exceptionThrown = false;
			try
			{
				CCommandParser commandParser;
				CCommand* command;

				command = commandParser.ParseCommand(str);
			}
			catch (InvalidParameterCountException& e)
			{
				exceptionThrown = true;
				Assert::AreEqual(std::string(e.what()), std::string("Invalid number of parameters : ") + parameters);
			}
			Assert::IsTrue(exceptionThrown);
		}

		void AssertParserThrowsInvalidCommandParameterValueException(std::string str, std::string param, std::string value)
		{
			bool exceptionThrown = false;
			try
			{
				CCommandParser commandParser;
				CCommand* command;

				command = commandParser.ParseCommand(str);
			}
			catch (InvalidCommandParameterValueException& e)
			{
				exceptionThrown = true;
				Assert::AreEqual(std::string(e.what()), std::string("Invalid parameter value : ") + param + std::string(" = ") + value);
			}
			Assert::IsTrue(exceptionThrown);
		}

		void AssertParserThrowsUnexpectedCommandParameterException(std::string str)
		{
			bool exceptionThrown = false;
			try
			{
				CCommandParser commandParser;
				CCommand* command;

				command = commandParser.ParseCommand(str);
			}
			catch (UnexpectedCommandParameterException& e)
			{
				exceptionThrown = true;
				Assert::AreEqual(std::string(e.what()), std::string("Unexpected command parameter"));
			}
			Assert::IsTrue(exceptionThrown);
		}
	
	public:
		TEST_METHOD(Test_ParseCommandReturnsNullForInvalidInput)
		{
			AssertParserThrowsInvalidCommandException("mOve 100", "mOve");

			AssertParserThrowsInvalidCommandException("!@#~", "!@#~");
		}

		TEST_METHOD(Test_ParseCommandReturnsPlaceCommand)
		{
			CCommandParser commandParser;
			CCommand* command;

			command = commandParser.ParseCommand("PLACE 4,1,NORTH");
			Assert::IsNotNull(command);
			Assert::AreEqual(true, command->IsPlace());
			AssertPlacement(command, 4, 1, CDirection::NORTH);
			Assert::AreEqual(false, command->IsMove());
			Assert::AreEqual(static_cast<int>(CRotate::NONE), 
				static_cast<int>(command->GetRotate()));
			Assert::AreEqual(false, command->DoReport());

			delete command;

			command = commandParser.ParseCommand("PLACE 1,2,EAST");
			Assert::IsNotNull(command);
			Assert::AreEqual(true, command->IsPlace());
			AssertPlacement(command, 1, 2, CDirection::EAST);
			Assert::AreEqual(false, command->IsMove());
			Assert::AreEqual(static_cast<int>(CRotate::NONE),
				static_cast<int>(command->GetRotate()));
			Assert::AreEqual(false, command->DoReport());

			delete command;

			command = commandParser.ParseCommand("PLACE 0,0,SOUTH");
			Assert::IsNotNull(command);
			Assert::AreEqual(true, command->IsPlace());
			AssertPlacement(command, 0, 0, CDirection::SOUTH);
			Assert::AreEqual(false, command->IsMove());
			Assert::AreEqual(static_cast<int>(CRotate::NONE),
				static_cast<int>(command->GetRotate()));
			Assert::AreEqual(false, command->DoReport());

			delete command;

			command = commandParser.ParseCommand("PLACE 3,2,WEST");
			Assert::IsNotNull(command);
			Assert::AreEqual(true, command->IsPlace());
			AssertPlacement(command, 3, 2, CDirection::WEST);
			Assert::AreEqual(false, command->IsMove());
			Assert::AreEqual(static_cast<int>(CRotate::NONE),
				static_cast<int>(command->GetRotate()));
			Assert::AreEqual(false, command->DoReport());

			delete command;
		}

		TEST_METHOD(Test_ParseCommandReturnsNullIfPlaceCommandHasInvalidParameter)
		{
			// missing parameter
			AssertParserThrowsInvalidInvalidParameterCountException("PLACE", "X,Y,F");
			AssertParserThrowsInvalidInvalidParameterCountException("PLACE 4", "X,Y,F");
			AssertParserThrowsInvalidInvalidParameterCountException("PLACE EAST", "X,Y,F");
			AssertParserThrowsInvalidInvalidParameterCountException("PLACE 4,1", "X,Y,F");
			AssertParserThrowsInvalidInvalidParameterCountException("PLACE 4,NORTH", "X,Y,F");
			AssertParserThrowsInvalidInvalidParameterCountException("PLACE 1,1,", "X,Y,F");

			// invalid parameter value
			AssertParserThrowsInvalidCommandParameterValueException("PLACE ,1,NORTH", "X", "");
			AssertParserThrowsInvalidCommandParameterValueException("PLACE 4,,NORTH", "Y", "");
			AssertParserThrowsInvalidCommandParameterValueException("PLACE -1,1,NORTH", "X", "-1");
			AssertParserThrowsInvalidCommandParameterValueException("PLACE 4,-1,NORTH", "Y", "-1");
			AssertParserThrowsInvalidCommandParameterValueException("PLACE 1,1,NORtH", "F", "NORtH");
		}

		TEST_METHOD(Test_ParseCommandReturnsMoveCommand)
		{
			CCommandParser commandParser;
			CCommand* command;

			command = commandParser.ParseCommand("MOVE");
			Assert::IsNotNull(command);
			Assert::AreEqual(false, command->IsPlace());
			AssertPlacementIsInitState(command);
			Assert::AreEqual(true, command->IsMove());
			Assert::AreEqual(static_cast<int>(CRotate::NONE), static_cast<int>(command->GetRotate()));
			Assert::AreEqual(false, command->DoReport());

			delete command;
		}

		TEST_METHOD(Test_ParseCommandReturnsNullIfMoveCommandHasParameter)
		{
			AssertParserThrowsUnexpectedCommandParameterException("MOVE x");
			AssertParserThrowsUnexpectedCommandParameterException("MOVE 1");
		}

		TEST_METHOD(Test_ParseCommandReturnsLeftCommand)
		{
			CCommandParser commandParser;
			CCommand* command;

			command = commandParser.ParseCommand("LEFT");
			Assert::IsNotNull(command);
			Assert::AreEqual(false, command->IsPlace());
			AssertPlacementIsInitState(command);
			Assert::AreEqual(false, command->IsMove());
			Assert::AreEqual(static_cast<int>(CRotate::LEFT), static_cast<int>(command->GetRotate()));
			Assert::AreEqual(false, command->DoReport());

			delete command;
		}

		TEST_METHOD(Test_ParseCommandReturnsNullIfLeftCommandHasParameter)
		{
			AssertParserThrowsUnexpectedCommandParameterException("LEFT x");
			AssertParserThrowsUnexpectedCommandParameterException("LEFT 1");
		}

		TEST_METHOD(Test_ParseCommandReturnsRightCommand)
		{
			CCommandParser commandParser;
			CCommand* command;

			command = commandParser.ParseCommand("RIGHT");
			Assert::IsNotNull(command);
			Assert::AreEqual(false, command->IsPlace());
			AssertPlacementIsInitState(command);
			Assert::AreEqual(false, command->IsMove());
			Assert::AreEqual(static_cast<int>(CRotate::RIGHT), static_cast<int>(command->GetRotate()));
			Assert::AreEqual(false, command->DoReport());

			delete command;
		}

		TEST_METHOD(Test_ParseCommandReturnsNullIfRightCommandHasParameter)
		{
			AssertParserThrowsUnexpectedCommandParameterException("RIGHT x");
			AssertParserThrowsUnexpectedCommandParameterException("RIGHT 1");
		}

		TEST_METHOD(Test_ParseCommandReturnsReportCommand)
		{
			CCommandParser commandParser;
			CCommand* command;

			command = commandParser.ParseCommand("REPORT");
			Assert::IsNotNull(command);
			Assert::AreEqual(false, command->IsPlace());
			AssertPlacementIsInitState(command);
			Assert::AreEqual(false, command->IsMove());
			Assert::AreEqual(static_cast<int>(CRotate::NONE), 
				static_cast<int>(command->GetRotate()));
			Assert::AreEqual(true, command->DoReport());

			delete command;
		}

		TEST_METHOD(Test_ParseCommandReturnsNullIfReportCommandHasParameter)
		{
			AssertParserThrowsUnexpectedCommandParameterException("REPORT x");
			AssertParserThrowsUnexpectedCommandParameterException("REPORT 1");
		}
	};
}
