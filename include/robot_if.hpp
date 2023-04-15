//******************************************************************************
/*! @file       robot_if.hpp
	@brief      External interface for constants and type definitions used for robot
*/
//******************************************************************************
#pragma once

#include <exception>

//******************************************************************************
//               Public definitions
//******************************************************************************

/**
* @brief Apply command result
*/
enum class CCommandApplyResult {
	OK,
	ERROR,
	ROBOT_NOT_YET_PLACED,
	INVALID_PLACE,
	IGNORE_FALL_OFF_MOVE
};

/**
* @brief exception when creating robot with null table
*/
struct RobotNullTableException : public std::exception
{
	const char* what() const throw ()
	{
		return "Unable to create robot with NULL table";
	}
};
