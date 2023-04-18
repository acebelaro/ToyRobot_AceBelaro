//******************************************************************************
/*! @file       command_parser.hpp
	@brief      External interface of command parser class
*/
//******************************************************************************
#pragma once


#include <regex>
#include <functional>
#include <map>
#include <iostream>

#include "robot.hpp"
#include "table.hpp"

using namespace std;

typedef function<void (const smatch & match)> tCommandExecuteFunction;

typedef map<string,tCommandExecuteFunction> tCommandRegexExecutionFunctionMap;

//******************************************************************************
//               Public definitions
//******************************************************************************

/* Command Parser class */
class CommandParser
{
	public:
		CommandParser(Robot&,Table&);
		~CommandParser() = default;

	private:
		Robot & _robot;
		Table & _table;

	private:
		tCommandRegexExecutionFunctionMap _commandRegexFunctionMap;
		void createCommands();
		
	public:
		bool parseCommand(string strCommand);
};
