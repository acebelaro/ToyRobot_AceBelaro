//******************************************************************************
/*! @file       table.cpp
	@brief      Source definition for table
*/
//******************************************************************************
#include "table.hpp"

//******************************************************************************
//               Class function definition
//******************************************************************************

Table::Table( int width, int height ):
	_width(width), _height(height)
{

}

int Table::GetWidth() const
{
	return _width;
}

void Table::SetWidth(int width)
{
	_width = width;
}

int Table::GetHeight() const
{
	return _height;
}

void Table::SetHeight(int height)
{
	_height = height;
}

bool Table::IsCoordinatesWithinBounds(const Coordinate& coordinate) const
{
	bool allowed = false;
	int x = coordinate.GetX();
	int y = coordinate.GetY();
	if( x >= 0 && y >= 0 && x < _width && y < _height )
	{
		allowed = true;
	}
	return allowed;
}
