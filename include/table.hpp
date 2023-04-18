//******************************************************************************
/*! @file       table.hpp
	@brief      External interface of table class
*/
//******************************************************************************
#pragma once

#include "coordinate.hpp"

//******************************************************************************
//               Public definitions
//******************************************************************************

class Table {
public:
	Table(int, int);
	~Table() = default;

private:
	int _width;		/* table width */
	int _height;	/* table height */

public:
	int GetWidth() const;
	void SetWidth(int);
	int GetHeight() const;
	void SetHeight(int);
	bool IsCoordinatesWithinBounds(const Coordinate&) const;
};
