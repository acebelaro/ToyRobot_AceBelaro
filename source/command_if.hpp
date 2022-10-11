//******************************************************************************
/*! @file       command_if.hpp
	@brief      External interface for constants and type definitions used for command
*/
//******************************************************************************
#pragma once

#include "table_if.hpp"

//******************************************************************************
//               Public macros
//******************************************************************************

/* Initial value for direction member of placement */
#define INIT_PLACEMENT_DIRECTION ( CDirection::NORTH )

//******************************************************************************
//               Public definitions
//******************************************************************************

/**
* @brief Direction values
*/
enum class CDirection {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

/**
* @brief Rotate values
*/
enum class CRotate {
	NONE, //  use for initial values to indicate no rotation
	LEFT,
	RIGHT,
};

/**
* @brief Placement parameter
*/
typedef struct stPlacement {
	stPosition position;
	CDirection direction;
	/**
	* @brief Initilizes placement member values
	*/
	stPlacement()
	{
		direction = INIT_PLACEMENT_DIRECTION;
	};
}stPlacement;

