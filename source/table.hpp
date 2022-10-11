//******************************************************************************
/*! @file       table.hpp
	@brief      External interface of table class
*/
//******************************************************************************
#pragma once

#include "table_if.hpp"

//******************************************************************************
//               Public definitions
//******************************************************************************

/** Table class */
class CTable {
public:
	/**
	* @brief Table constructor
	* @param width	- width of table
	* @param height	- height of table
	*/
	CTable(int, int);
	/**
	* @brief Table deconstructor
	*/
	~CTable();
private:
	int m_width;	/* table width */
	int m_height;	/* table height */
public:
	/**
	* @brief Gets table width
	* @return table width
	*/
	int GetWidth();
	/**
	* @brief Gets table height
	* @return table height
	*/
	int GetHeight();
	/**
	* @brief Checks if position is allowed in table.
	* @param position	- position to check in table
	* @retval true		- position is allowed
	* @retval false		- position is not allowed
	*/
	bool IsPositionAllowed(stPosition const*);
};
