//******************************************************************************
/*! @file       table_if.hpp
	@brief      External interface for constants and type definitions used for table
*/
//******************************************************************************
#pragma once

#include <exception>

//******************************************************************************
//               Public macros
//******************************************************************************

#define INIT_X_POS ( 0 )	/* Initial value for X coordinate of position */
#define INIT_Y_POS ( 0 )	/* Initial value for Y coordinate of position */

//******************************************************************************
//               Public definitions
//******************************************************************************

/**
* @brief Position
*/
typedef struct stPosition {
	int x;
	int y;
	/**
	* @brief Initilizes position member values
	*/
	stPosition()
	{
		x = INIT_X_POS;
		y = INIT_Y_POS;
	};
	/**
	* @brief Copies position value
	*/
	void Copy(stPosition const* src)
	{
		x = src->x;
		y = src->y;
	}
}stPosition;

/**
* @brief exception when creating table invalid size
*/
struct TableInvalidSizeException : public std::exception
{
	const char* what() const throw ()
	{
		return "Unable to create size with non-positive width and/or height";
	}
};
