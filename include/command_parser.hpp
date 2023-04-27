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

#include "command.hpp"

using namespace std;

typedef function<void (const smatch&, UPTR_COMMAND&)> tCommandExecuteFunction;

typedef map<string,tCommandExecuteFunction> tCommandRegexExecutionFunctionMap;

//******************************************************************************
//               Public definitions
//******************************************************************************

/* Command Parser class */
class CommandParser
{
	public:
		CommandParser();
		~CommandParser() = default;

	private:
		tCommandRegexExecutionFunctionMap _commandRegexFunctionMap;
		void createCommands();
		
	public:
		bool parseCommand(string, UPTR_COMMAND&);
};
