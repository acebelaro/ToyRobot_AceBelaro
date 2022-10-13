//******************************************************************************
/*! @file       command_parser_if.hpp
	@brief      External interface for constants and type definitions used for command parser
*/
//******************************************************************************
#pragma once

#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <map>
#include "command.hpp"
#if defined(WORK_AROUND_STRDUP)
#include "util.hpp"
#endif // WORK_AROUND_STRDUP

/* workaround definition for _strdup */
#if defined(WORK_AROUND_STRDUP)
#define STRDUP wa_strdup
#else
#define STRDUP _strdup	
#endif // WORK_AROUND_STRDUP

//******************************************************************************
//               Public macros
//******************************************************************************

#define EXCEPTION_MESSAGE_LEN	( 100u )	// length of exception message buffer

//******************************************************************************
//               Public definitions
//******************************************************************************

/* String vector definition */
typedef std::vector<std::string> tStringVector;

/* Command parser function parameter definition */
typedef tStringVector tCommandParserFuncParam;

/* Command parser function definition */
typedef CCommand* (*tCommandParserFunc)(tCommandParserFuncParam);

/* Command name to command parser function map */
typedef std::map<std::string, tCommandParserFunc> tCommandParserMap;

/* Command parser parameter defintition */
typedef struct stCommandParseParam {
	std::string commandName;
	tStringVector params;
	/*
	* @brief Initializes command parser parameter member
	*/
	stCommandParseParam() {
		commandName = "";
	}
}stCommandParseParam;

/* Base command parser exception */
struct ParserCommandException : public std::exception
{
	
};

/**
* @brief exception for invalid command
*/
struct InvalidCommandException : public ParserCommandException
{
	std::string commandName;
	InvalidCommandException(std::string commandName)
	{
		this->commandName = commandName;
	}
	const char* what() const throw ()
	{
		char buffer[EXCEPTION_MESSAGE_LEN] = { 0 }; //Must be big enough

		// writing printf output in buffer
		snprintf(buffer, EXCEPTION_MESSAGE_LEN, "Invalid command : %s", commandName.c_str());

		// duplicate if needed
		return STRDUP(buffer);
	}
};

/**
* @brief exception when command has invalid count of parameter
*/
struct InvalidParameterCountException : public ParserCommandException
{
	std::string parameters;
	InvalidParameterCountException(std::string parameters)
	{
		this->parameters = parameters;
	}
	const char* what() const throw ()
	{
		char buffer[EXCEPTION_MESSAGE_LEN] = { 0 }; //Must be big enough

		// writing printf output in buffer
		snprintf(buffer, EXCEPTION_MESSAGE_LEN, "Invalid number of parameters : %s", parameters.c_str());

		// duplicate if needed
		return STRDUP(buffer);
	}
};

/**
* @brief exception when command has unexpected parameter
*/
struct UnexpectedCommandParameterException : public ParserCommandException
{
	UnexpectedCommandParameterException()
	{

	}
	const char* what() const throw ()
	{
		return "Unexpected command parameter";
	}
};

/**
* @brief exception when parameter has invalid value
*/
struct InvalidCommandParameterValueException : public ParserCommandException
{
	std::string param;
	std::string value;
	InvalidCommandParameterValueException(std::string param, std::string value)
	{
		this->param = param;
		this->value = value;
	}
	const char* what() const throw ()
	{
		char buffer[EXCEPTION_MESSAGE_LEN] = { 0 }; //Must be big enough

		// writing printf output in buffer
		snprintf(buffer, EXCEPTION_MESSAGE_LEN, "Invalid parameter value : %s = %s", param.c_str(), value.c_str());

		// duplicate if needed
		return STRDUP(buffer);
	}
};
