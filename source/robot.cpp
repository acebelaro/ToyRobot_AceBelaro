//******************************************************************************
/*! @file       robot.cpp
	@brief      Source definition for robot
*/
//******************************************************************************
#include <iostream>
#include <sstream>
#include "robot.hpp"

//******************************************************************************
//               Class function definition
//******************************************************************************

Robot::Robot():
	_position(nullptr)
{
	m_isPlaced = false;
}

void Robot::Place(const RobotPosition& position, const Table& table)
{
	if( table.IsCoordinatesWithinBounds(position.GetCoordinate()) )
	{
		m_isPlaced = true;
		_position.reset(new RobotPosition(position));
	}
}

void Robot::RotateLeft()
{
	if( nullptr != _position )
	{
		Direction direction = _position->GetDirection();
		int dirInt = static_cast<int>(direction) - 1;
		if( dirInt < MIN_DIR )
		{
			dirInt = MAX_DIR;
		}
		direction = static_cast<Direction>(dirInt);
		_position->SetDirection(direction );
	}
}

void Robot::RotateRight()
{
	if( nullptr != _position )
	{
		Direction direction = _position->GetDirection();
		int dirInt = static_cast<int>(direction) + 1;
		if( dirInt > MAX_DIR )
		{
			dirInt = MIN_DIR;
		}
		direction = static_cast<Direction>(dirInt);
		_position->SetDirection(direction);
	}
}

bool Robot::Move(const Table& table)
{
	bool result = false;

	if( nullptr != _position )
	{
		Coordinate coordinate = _position->GetCoordinate();
		int x = coordinate.GetX();
		int y = coordinate.GetY();
		switch(_position->GetDirection())
		{
			case Direction::NORTH:
				y++;
				break;
			case Direction::EAST:
				x++;
				break;
			case Direction::SOUTH:
				y--;
				break;
			case Direction::WEST:
				x--;
				break;
		}
		Coordinate newCoordinate(x,y);
		if(table.IsCoordinatesWithinBounds(newCoordinate))
		{
			result = true;
			_position->SetCoordinate(newCoordinate);
		}
	}

	return result;
}

string Robot::Report() const
{
    stringstream report;
    if( nullptr != _position )
	{
		string direction(DirectionToString(_position->GetDirection()));
        report << _position->GetCoordinate().GetX() << "," << _position->GetCoordinate().GetY() << "," << direction;   
    }
	else
	{		
		report << "Robot not yet placed";
    }
    return report.str();
}

bool Robot::IsPlaced() const
{
	return m_isPlaced;
}

Direction Robot::GetDirection() const
{
	return ( nullptr != _position )?
		_position->GetDirection() :
		Direction::NORTH;
}

Coordinate Robot::GetCoordinate() const
{
	return ( nullptr != _position )?
		_position->GetCoordinate() :
		Coordinate(0,0);
}
