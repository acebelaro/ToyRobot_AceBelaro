//******************************************************************************
/*! @file       coordinate.cpp
	@brief      Source definition for Coordinate
*/
//******************************************************************************

#include "coordinate.hpp"

Coordinate::Coordinate(int x, int y):
    _x(x), _y(y)
{

}

int Coordinate::GetX() const
{
    return _x;
}

int Coordinate::GetY() const
{
    return _y;
}

void Coordinate::SetX(int x)
{
    _x = x;
}

void Coordinate::SetY(int y)
{
    _y = y;
}

bool operator==(const Coordinate& lhs, const Coordinate& rhs)
{
    return lhs.GetX() == rhs.GetX() && lhs.GetY() == rhs.GetY();
}
