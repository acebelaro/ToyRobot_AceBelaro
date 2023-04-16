//******************************************************************************
/*! @file       command_parser.cpp
	@brief      Source definition for command parser
*/
//******************************************************************************
#include "command_parser.hpp"
#include <iostream>

//******************************************************************************
//               Private macros
//******************************************************************************

//******************************************************************************
//               Class function definition
//******************************************************************************

CommandParser::CommandParser(Robot& robot,Table& table):
	_robot(robot), _table(table)
{
	createCommands();
}

void CommandParser::createCommands()
{
	_commandRegexFunctionMap.insert(make_pair(
		"^\\s*(PLACE)\\s+([0-9])+\\s*,\\s*([0-9]+)\\s*,\\s*(NORTH|SOUTH|EAST|WEST)\\s*$",
		[&] (const smatch & match)
		{
			int x = stoi(match[2]);
			int y = stoi(match[3]);
			string directionStr = string(match[4]);
			Direction direction = StringToDirection(directionStr);
			Coordinate coordinate(x,y);
			RobotPosition position(coordinate,direction);
			_robot.Place(position,_table);
		}
	));

	_commandRegexFunctionMap.insert(make_pair(
		"^\\s*MOVE\\s*$",
		[&] (const smatch & match)
		{
			_robot.Move(_table);
		}
	));

	_commandRegexFunctionMap.insert(make_pair(
		"^\\s*LEFT\\s*$",
		[&] (const smatch & match)
		{
			_robot.RotateLeft();
		}
	));

	_commandRegexFunctionMap.insert(make_pair(
		"^\\s*RIGHT\\s*$",
		[&] (const smatch & match)
		{
			_robot.RotateRight();
		}
	));

	_commandRegexFunctionMap.insert(make_pair(
		"^\\s*REPORT\\s*$",
		[&] (const smatch & match)
		{
			stringstream report;
			report << "Output : " << _robot.Report();
			cout << report.str() << endl;
		}
	));
}

bool CommandParser::parseCommand(string strCommand)
{
	bool res = false;
	for( auto & it: _commandRegexFunctionMap )
	{
		regex rgx(it.first, regex_constants::icase);
		smatch match;
		if( it.second && regex_search(strCommand, match, rgx) )
		{
			it.second(match);
			res = true;
			break;
		}
	}
	return res;
}
