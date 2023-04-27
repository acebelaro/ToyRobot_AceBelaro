//******************************************************************************
/*! @file       command_parser.cpp
	@brief      Source definition for command parser
*/
//******************************************************************************

#include <iostream>
#include <sstream>

#include "command_parser.hpp"
#include "place_command.hpp"
#include "move_command.hpp"
#include "rotate_command.hpp"
#include "report_command.hpp"

//******************************************************************************
//               Private macros
//******************************************************************************

//******************************************************************************
//               Class function definition
//******************************************************************************

CommandParser::CommandParser()
{
	createCommands();
}

void CommandParser::createCommands()
{
	_commandRegexFunctionMap.insert(make_pair(
		PlaceCommand::PATTERN,
		[](const smatch & match, UPTR_COMMAND &cmd)
		{
			int x = stoi(match[2]);
			int y = stoi(match[3]);
			string directionStr = string(match[4]);
			Direction direction = StringToDirection(directionStr);
			Coordinate coordinate(x,y);
			RobotPosition position(coordinate,direction);
			cmd.reset(new PlaceCommand(position));
		}
	));

	_commandRegexFunctionMap.insert(make_pair(
		MoveCommand::PATTERN,
		[](const smatch & match, UPTR_COMMAND &cmd)
		{
			cmd.reset(new MoveCommand());
		}
	));

	_commandRegexFunctionMap.insert(make_pair(
		RotateCommand::PATTERN,
		[](const smatch & match, UPTR_COMMAND &cmd)
		{
			if( 0 == match[1].compare("LEFT") )
			{
				cmd.reset(new RotateCommand(Rotate::LEFT));
			}
			else if( 0 == match[1].compare("RIGHT") )
			{
				cmd.reset(new RotateCommand(Rotate::RIGHT));
			}
		}
	));

	_commandRegexFunctionMap.insert(make_pair(
		ReportCommand::PATTERN,
		[](const smatch & match, UPTR_COMMAND &cmd)
		{
			cmd.reset(new ReportCommand());
		}
	));
}

bool CommandParser::parseCommand(string strCommand, UPTR_COMMAND &cmd)
{
	bool res = false;
	for( auto & it: _commandRegexFunctionMap )
	{
		regex rgx(it.first, regex_constants::icase);
		smatch match;
		if( it.second && regex_search(strCommand, match, rgx) )
		{
			it.second(match,cmd);
			res = true;
			break;
		}
	}
	return res;
}
