//******************************************************************************
/*! @file       command_parser.cpp
	@brief      Source definition for command parser
*/
//******************************************************************************
#include "command_parser.hpp"
#include "util.hpp"
#include <iostream>

//******************************************************************************
//               Private macros
//******************************************************************************

#define COMMAND_TOKEN_TARGET_LENGTH	( (size_t) 2 )	/* Target token count for valid command after split */
#define COMMAND_STRING_DELIMITER	( ' ' )			/* Delimiter to split command string */
#define PARAMETER_STRING_DELIMITER	( ',' )			/* Delimiter to split parameter string */

#define PLACE_COMMAND_EXPECTED_PARAMETER_COUNT	( (size_t) 3 )	/* Place command expected parameter count*/
#define PLACE_COMMAND_PARAMETER					( "X,Y,F" )		/* Place command parameter */
#define PLACE_COMMAND_PARAM_NAME_X				( "X" )			/* Place command paramter X */
#define PLACE_COMMAND_PARAM_NAME_Y				( "Y" )			/* Place command paramter Y */
#define PLACE_COMMAND_PARAM_NAME_F				( "F" )			/* Place command paramter F */

//******************************************************************************
//               Class function definition
//******************************************************************************

CCommandParser::CCommandParser()
{
	// create command map
	m_commandParserMap["PLACE"] = CCommandParser::ParsePlaceCommand;
	m_commandParserMap["MOVE"] = CCommandParser::ParseMoveCommand;
	m_commandParserMap["LEFT"] = CCommandParser::ParseLeftCommand;
	m_commandParserMap["RIGHT"] = CCommandParser::ParseRightCommand;
	m_commandParserMap["REPORT"] = CCommandParser::ParseReportCommand;
	// to add commands, create function parser and add to map
}

CCommandParser::~CCommandParser()
{
}

CCommand* CCommandParser::ParsePlaceCommand(tCommandParserFuncParam params)
{
	CCommand* command = nullptr;
	if (PLACE_COMMAND_EXPECTED_PARAMETER_COUNT == params.size()) {
		int index = 0;
		bool error = true;
		std::string point;
		stPlacement placement;
		point = params[index++];
		if (0 < point.length() && IsPositiveIntegerString(point)) {
			// OK x param
			placement.position.x = std::stoi(point);
			point = params[index++];
			if (0 < point.length() && IsPositiveIntegerString(point)) {
				// OK y param
				placement.position.y = std::stoi(point);
				std::string directionName = params[index];
				if (StringToDirection(directionName, &placement.direction)) {
					// valid direction param
					error = false;
				}
				else
				{
					// invalid direction
					throw InvalidCommandParameterValueException(PLACE_COMMAND_PARAM_NAME_F, directionName);
				}
			}
			else
			{
				// invalid y
				throw InvalidCommandParameterValueException(PLACE_COMMAND_PARAM_NAME_Y, point);
			}
		}
		else
		{
			// invalid x
			throw InvalidCommandParameterValueException(PLACE_COMMAND_PARAM_NAME_X, point);
		}
		if (false == error) {
			command = new CCommand();
			command->SetPlacement(placement);
		}
	}
	else
	{
		// expecting parameter
		throw InvalidParameterCountException(PLACE_COMMAND_PARAMETER);
	}
	return command;
}

CCommand* CCommandParser::ParseMoveCommand(tCommandParserFuncParam params)
{
	CCommand* command = nullptr;
	if (0 == params.size()) {
		command = new CCommand();
		command->SetMove(true);
	}
	else
	{
		throw UnexpectedCommandParameterException();
	}
	return command;
}

CCommand* CCommandParser::ParseLeftCommand(tCommandParserFuncParam params)
{
	CCommand* command = nullptr;
	if (0 == params.size()) {
		command = new CCommand();
		command->SetRotate(CRotate::LEFT);
	}
	else
	{
		throw UnexpectedCommandParameterException();
	}
	return command;
}

CCommand* CCommandParser::ParseRightCommand(tCommandParserFuncParam params)
{
	CCommand* command = nullptr;
	if (0 == params.size()) {
		command = new CCommand();
		command->SetRotate(CRotate::RIGHT);
	}
	else
	{
		throw UnexpectedCommandParameterException();
	}
	return command;
}

CCommand* CCommandParser::ParseReportCommand(tCommandParserFuncParam params)
{
	CCommand* command = nullptr;
	if (0 == params.size()) {
		command = new CCommand();
		command->SetReport(true);
	}
	else
	{
		throw UnexpectedCommandParameterException();
	}
	return command;
}

stCommandParseParam CCommandParser::ParseCommandParam(std::string str)
{
	stCommandParseParam param;

	// split command and params
	tStringVector cmdTokens;

	SplitString(str, COMMAND_STRING_DELIMITER, cmdTokens);
	size_t s = cmdTokens.size();
	if (COMMAND_TOKEN_TARGET_LENGTH >= s)
	{
		param.commandName = cmdTokens[0];
		if (COMMAND_TOKEN_TARGET_LENGTH == s) {
			// split params
			SplitString(cmdTokens[1], PARAMETER_STRING_DELIMITER, param.params);
		}
	}
	return param;
}

CCommand* CCommandParser::ParseCommand(std::string str)
{
	CCommand* command = nullptr;

	if (0 < str.length()) {
		CommandParserMap::iterator it;
		stCommandParseParam commandParseParam = ParseCommandParam(str);

		for (it = m_commandParserMap.begin(); it != m_commandParserMap.end(); it++)
		{
			if (it->first == commandParseParam.commandName)
			{
				command = it->second(commandParseParam.params);
				break;
			}
		}
		if (nullptr == command)
		{
			// input does not match with command names
			throw InvalidCommandException(commandParseParam.commandName);
		}
	}
	return command;
}
