//******************************************************************************
/*! @file       command_parser.hpp
	@brief      External interface of command parser class
*/
//******************************************************************************
#pragma once

#include "command_parser_if.hpp"

//******************************************************************************
//               Public definitions
//******************************************************************************

/* Command Parser class */
class CCommandParser {
public:
	/**
	* @brief Command parser constructor
	*/
	CCommandParser();
	/**
	* @brief Command parser deconstructor
	*/
	~CCommandParser();
private:
	tCommandParserMap m_commandParserMap;	/* command name to parser map */
	/**
	* @brief Parses input to create command parameter
	* @param str	- input string
	* @return command parser parameter
	*/
	stCommandParseParam ParseCommandParam(std::string);
	/*
	* @brief Parser for PLACE command
	* @param params		- command parser function parameter
	* @return			- PLACE command (NULL if error)
	*/
	static CCommand* ParsePlaceCommand(tCommandParserFuncParam);
	/*
	* @brief Parser for MOVE command
	* @param params		- command parser function parameter
	* @return			- MOVE command (NULL if error)
	*/
	static CCommand* ParseMoveCommand(tCommandParserFuncParam);

	/*
	* @brief Parser for LEFT command
	* @param params		- command parser function parameter
	* @return			- LEFT command (NULL if error)
	*/
	static CCommand* ParseLeftCommand(tCommandParserFuncParam);

	/*
	* @brief Parser for RIGHT command
	* @param params		- command parser function parameter
	* @return			- RIGHT command (NULL if error)
	*/
	static CCommand* ParseRightCommand(tCommandParserFuncParam);

	/*
	* @brief Parser for REPORT command
	* @param params		- command parser function parameter
	* @return			- REPORT command (NULL if error)
	*/
	static CCommand* ParseReportCommand(tCommandParserFuncParam);
public:
	/**
	* @brief Parser command input string to create command
	* @param str	- input string
	* @return command (NULL if error)
	* @exception	InvalidCommandException					- if command is not found
	* @exception	InvalidParameterCountException			- when command has invalid parameter count
	* @exception	InvalidCommandParameterValueException	- when command has invalid parameter
	* @exception	UnexpectedCommandParameterException		- when command has unexpected parameter
	*/
	CCommand* ParseCommand(std::string);
};
