//******************************************************************************
/*! @file       test_command_parser.cpp
	@brief      Unit test for command parser
*/
//******************************************************************************

#include "gtest/gtest.h"
#include "command_parser.hpp"
#include "test_helper.h"

//******************************************************************************
//               Private function declaration
//******************************************************************************

/*
* @brief Test helper to assert PLACE command
* @param command
* @param x
* @param y
* @param direction
*/
void AssertPlacement(CCommand* command, int x, int y, CDirection direction);

/*
* @brief Test helper to assert PLACE command is initial state
* @param command
*/
void AssertPlacementIsInitState(CCommand* command);

/*
* @brief Test helper to assert parser throws InvalidCommandException
* @param str
* @param commandName
*/
void AssertParserThrowsInvalidCommandException(std::string str, std::string commandName);

/*
* @brief Test helper to assert parser throws InvalidParameterCountException
* @param str
* @param parameters
*/
void AssertParserThrowsInvalidInvalidParameterCountException(std::string str, std::string parameters);

/*
* @brief Test helper to assert parser throws InvalidCommandParameterValueException
* @param str
* @param param
* @param value
*/
void AssertParserThrowsInvalidCommandParameterValueException(std::string str, std::string param, std::string value);

/*
* @brief Test helper to assert parser throws UnexpectedCommandParameterException
* @param str
*/
void AssertParserThrowsUnexpectedCommandParameterException(std::string str);

//******************************************************************************
//               Private function definition
//******************************************************************************

void AssertPlacement(CCommand* command, int x, int y, CDirection direction) {
	stPlacement placement = command->GetPlacement();
	EXPECT_EQ(static_cast<int>(direction),
		static_cast<int>(placement.direction));
	EXPECT_EQ(x, placement.position.x);
	EXPECT_EQ(y, placement.position.y);
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

		commandParser.ParseCommand(str);
	}
	catch (InvalidCommandException& e)
	{
		exceptionThrown = true;
		EXPECT_EQ(std::string(e.what()), std::string("Invalid command : ") + commandName);
	}
	EXPECT_TRUE(exceptionThrown);
}

void AssertParserThrowsInvalidInvalidParameterCountException(std::string str, std::string parameters)
{
	bool exceptionThrown = false;
	try
	{
		CCommandParser commandParser;

		commandParser.ParseCommand(str);
	}
	catch (InvalidParameterCountException& e)
	{
		exceptionThrown = true;
		EXPECT_EQ(std::string(e.what()), std::string("Invalid number of parameters : ") + parameters);
	}
	EXPECT_TRUE(exceptionThrown);
}

void AssertParserThrowsInvalidCommandParameterValueException(std::string str, std::string param, std::string value)
{
	bool exceptionThrown = false;
	try
	{
		CCommandParser commandParser;

		commandParser.ParseCommand(str);
	}
	catch (InvalidCommandParameterValueException& e)
	{
		exceptionThrown = true;
		EXPECT_EQ(std::string(e.what()), std::string("Invalid parameter value : ") + param + std::string(" = ") + value);
	}
	EXPECT_TRUE(exceptionThrown);
}

void AssertParserThrowsUnexpectedCommandParameterException(std::string str)
{
	bool exceptionThrown = false;
	try
	{
		CCommandParser commandParser;

		commandParser.ParseCommand(str);
	}
	catch (UnexpectedCommandParameterException& e)
	{
		exceptionThrown = true;
		EXPECT_EQ(std::string(e.what()), std::string("Unexpected command parameter"));
	}
	EXPECT_TRUE(exceptionThrown);
}

//******************************************************************************
//               Test functions
//******************************************************************************

/*! @brief Test parser throws exception when command is not valid
*/
TEST( TestCommandParser, Test_ParseCommandReturnsNullForInvalidInput)
{
	AssertParserThrowsInvalidCommandException("mOve 100", "mOve");

	AssertParserThrowsInvalidCommandException("!@#~", "!@#~");
}

/*! @brief Test parser returns PLACE command
*/
TEST( TestCommandParser, Test_ParseCommandReturnsPlaceCommand)
{
	CCommandParser commandParser;
	CCommand* command;

	command = commandParser.ParseCommand("PLACE 4,1,NORTH");
	EXPECT_IS_NOT_NULL(command);
	EXPECT_EQ(true, command->IsPlace());
	AssertPlacement(command, 4, 1, CDirection::NORTH);
	EXPECT_EQ(false, command->IsMove());
	EXPECT_EQ(static_cast<int>(CRotate::NONE), 
		static_cast<int>(command->GetRotate()));
	EXPECT_EQ(false, command->DoReport());

	delete command;

	command = commandParser.ParseCommand("PLACE 1,2,EAST");
	EXPECT_IS_NOT_NULL(command);
	EXPECT_EQ(true, command->IsPlace());
	AssertPlacement(command, 1, 2, CDirection::EAST);
	EXPECT_EQ(false, command->IsMove());
	EXPECT_EQ(static_cast<int>(CRotate::NONE),
		static_cast<int>(command->GetRotate()));
	EXPECT_EQ(false, command->DoReport());

	delete command;

	command = commandParser.ParseCommand("PLACE 0,0,SOUTH");
	EXPECT_IS_NOT_NULL(command);
	EXPECT_EQ(true, command->IsPlace());
	AssertPlacement(command, 0, 0, CDirection::SOUTH);
	EXPECT_EQ(false, command->IsMove());
	EXPECT_EQ(static_cast<int>(CRotate::NONE),
		static_cast<int>(command->GetRotate()));
	EXPECT_EQ(false, command->DoReport());

	delete command;

	command = commandParser.ParseCommand("PLACE 3,2,WEST");
	EXPECT_IS_NOT_NULL(command);
	EXPECT_EQ(true, command->IsPlace());
	AssertPlacement(command, 3, 2, CDirection::WEST);
	EXPECT_EQ(false, command->IsMove());
	EXPECT_EQ(static_cast<int>(CRotate::NONE),
		static_cast<int>(command->GetRotate()));
	EXPECT_EQ(false, command->DoReport());

	delete command;
}

/*! @brief Test parser throws exception when PLACE command has invalid parameters
*/
TEST( TestCommandParser, Test_ParseCommandReturnsNullIfPlaceCommandHasInvalidParameter)
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

/*! @brief Test parser returns MOVE command
*/
TEST( TestCommandParser, Test_ParseCommandReturnsMoveCommand)
{
	CCommandParser commandParser;
	CCommand* command;

	command = commandParser.ParseCommand("MOVE");
	EXPECT_IS_NOT_NULL(command);
	EXPECT_EQ(false, command->IsPlace());
	AssertPlacementIsInitState(command);
	EXPECT_EQ(true, command->IsMove());
	EXPECT_EQ(static_cast<int>(CRotate::NONE), static_cast<int>(command->GetRotate()));
	EXPECT_EQ(false, command->DoReport());

	delete command;
}

/*! @brief Test parser throws exception when MOVE command has parameter
*/
TEST( TestCommandParser, Test_ParseCommandReturnsNullIfMoveCommandHasParameter)
{
	AssertParserThrowsUnexpectedCommandParameterException("MOVE x");
	AssertParserThrowsUnexpectedCommandParameterException("MOVE 1");
}

/*! @brief Test parser returns LEFT command
*/
TEST( TestCommandParser, Test_ParseCommandReturnsLeftCommand)
{
	CCommandParser commandParser;
	CCommand* command;

	command = commandParser.ParseCommand("LEFT");
	EXPECT_IS_NOT_NULL(command);
	EXPECT_EQ(false, command->IsPlace());
	AssertPlacementIsInitState(command);
	EXPECT_EQ(false, command->IsMove());
	EXPECT_EQ(static_cast<int>(CRotate::LEFT), static_cast<int>(command->GetRotate()));
	EXPECT_EQ(false, command->DoReport());

	delete command;
}

/*! @brief Test parser throws exception when LEFT command has parameter
*/
TEST( TestCommandParser, Test_ParseCommandReturnsNullIfLeftCommandHasParameter)
{
	AssertParserThrowsUnexpectedCommandParameterException("LEFT x");
	AssertParserThrowsUnexpectedCommandParameterException("LEFT 1");
}

/*! @brief Test parser returns RIGHT command
*/
TEST( TestCommandParser, Test_ParseCommandReturnsRightCommand)
{
	CCommandParser commandParser;
	CCommand* command;

	command = commandParser.ParseCommand("RIGHT");
	EXPECT_IS_NOT_NULL(command);
	EXPECT_EQ(false, command->IsPlace());
	AssertPlacementIsInitState(command);
	EXPECT_EQ(false, command->IsMove());
	EXPECT_EQ(static_cast<int>(CRotate::RIGHT), static_cast<int>(command->GetRotate()));
	EXPECT_EQ(false, command->DoReport());

	delete command;
}

/*! @brief Test parser throws exception when RIGHT command has parameter
*/
TEST( TestCommandParser, Test_ParseCommandReturnsNullIfRightCommandHasParameter)
{
	AssertParserThrowsUnexpectedCommandParameterException("RIGHT x");
	AssertParserThrowsUnexpectedCommandParameterException("RIGHT 1");
}

/*! @brief Test parser returns REPORT command
*/
TEST( TestCommandParser, Test_ParseCommandReturnsReportCommand)
{
	CCommandParser commandParser;
	CCommand* command;

	command = commandParser.ParseCommand("REPORT");
	EXPECT_IS_NOT_NULL(command);
	EXPECT_EQ(false, command->IsPlace());
	AssertPlacementIsInitState(command);
	EXPECT_EQ(false, command->IsMove());
	EXPECT_EQ(static_cast<int>(CRotate::NONE), 
		static_cast<int>(command->GetRotate()));
	EXPECT_EQ(true, command->DoReport());

	delete command;
}

/*! @brief Test parser throws exception when REPORT command has parameter
*/
TEST( TestCommandParser, Test_ParseCommandReturnsNullIfReportCommandHasParameter)
{
	AssertParserThrowsUnexpectedCommandParameterException("REPORT x");
	AssertParserThrowsUnexpectedCommandParameterException("REPORT 1");
}
