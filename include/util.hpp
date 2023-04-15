//******************************************************************************
/*! @file       util.hpp
	@brief      External interface of utilities
*/
//******************************************************************************
#pragma once

#include <vector>
#include <string>
#include "command_if.hpp"

//******************************************************************************
//               Public function declaration
//******************************************************************************

/*
* @brief Checks if string is positive integer
* @param str		- string to check
* @retval true		- string is positive integer
* @retval false		- string is not positive integer
*/
#define IsPositiveIntegerString(str) (str.find_first_not_of("0123456789") == std::string::npos)

/*
* @brief Splits string using delimiter
* @param str		- string to split
* @param delimiter	- split delimiter to use
* @param dest		- destination of split strings
*/
void SplitString(std::string, char, std::vector<std::string>&);

/*
* @brief Gets the direction equivalent of string
* @param directionName	- direction name
* @param direction		- destination of direction value
* @retval	true		- direction name is valid
* @retval	false		- direction name is invalid
*/
bool StringToDirection(std::string, CDirection*);

/*
* @brief Gets the string equivalent of direction
* @param directionValue	- direction value
* @return				- direction name
*/
std::string DirectionToString(CDirection);

#if defined(WORK_AROUND_STRDUP)
extern "C"
{
	/**
	* @brief workaround definition
	*/
	char* wa_strdup(const char* s);
}
#endif // WORK_AROUND_STRDUP
