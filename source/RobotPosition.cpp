//******************************************************************************
/*! @file       RobotPosition.cpp
	@brief      Source definition for Robot Position
*/
//******************************************************************************

#include "RobotPosition.hpp"

//******************************************************************************
//               Public definitions
//******************************************************************************

RobotPosition::RobotPosition(const Coordinate& coordinate, Direction direction):
    _coordinate( coordinate ),
    _direction( direction )
{

}

const Coordinate& RobotPosition::GetCoordinate() const
{
    return _coordinate;
}

void RobotPosition::SetCoordinate(Coordinate& coordinate)
{
    _coordinate = coordinate;
}

Direction RobotPosition::GetDirection() const
{
    return _direction;
}

void RobotPosition::SetDirection(Direction direction)
{
    _direction = direction;
}
