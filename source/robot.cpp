//******************************************************************************
/*! @file       robot.cpp
	@brief      Source definition for robot
*/
//******************************************************************************
#include <iostream>
#include "robot.hpp"
#include "util.hpp"

//******************************************************************************
//               Class function definition
//******************************************************************************

CRobot::CRobot(CTable* const table)
{
	if (nullptr != table)
	{
		m_table = table;
		m_isPlaced = false;
		m_direction = CDirection::NORTH;
	}
	else
	{
		throw RobotNullTableException();
	}
}

CRobot::~CRobot()
{
	// Do nothing
}

bool CRobot::Move()
{
	bool result = false;

	stPosition newPosition;
	newPosition.Copy(&m_position);
	switch (m_direction)
	{
	case CDirection::NORTH:
		newPosition.y++;
		break;
	case CDirection::EAST:
		newPosition.x++;
		break;
	case CDirection::SOUTH:
		newPosition.y--;
		break;
	case CDirection::WEST:
		newPosition.x--;
		break;
	}

	if (m_table->IsPositionAllowed(&newPosition))
	{
		m_position.Copy(&newPosition);
		result = true;
	}

	return result;
}

void CRobot::Rotate(CRotate rotate)
{
	switch (rotate) {
	case CRotate::NONE:
		// no rotate command
		break;
	case CRotate::LEFT:
		if (m_direction == CDirection::NORTH)
		{
			// overflow
			m_direction = CDirection::WEST;
		}
		else {
			// decrement since direction enum is defined to ascending values as clockwise
			m_direction = static_cast<CDirection>(static_cast<int>(m_direction) - 1);
		}
		break;
	case CRotate::RIGHT:
		if (m_direction == CDirection::WEST)
		{
			// overflow
			m_direction = CDirection::NORTH;
		}
		else {
			// increment since direction enum is defined to ascending values as clockwise
			m_direction = static_cast<CDirection>(static_cast<int>(m_direction) + 1);
		}
		break;
	}
}

CTable* CRobot::GetTable()
{
	return m_table;
}

bool CRobot::IsPlaced()
{
	return m_isPlaced;
}

CDirection CRobot::GetDirection()
{
	return m_direction;
}

stPosition CRobot::GetPosition()
{
	return m_position;
}

CCommandApplyResult CRobot::ApplyCommand(CCommand* const command)
{
	CCommandApplyResult result = CCommandApplyResult::ERROR;

	if (nullptr != command && nullptr != m_table)
	{
		if (command->IsPlace())
		{
			stPlacement placement = command->GetPlacement();
			if (m_table->IsPositionAllowed(&placement.position))
			{
				// update position
				m_position.Copy(&placement.position);
				m_direction = placement.direction;
				m_isPlaced = true;
				result = CCommandApplyResult::OK;
			}
			else
			{
				result = CCommandApplyResult::INVALID_PLACE;
			}
		}
		else {
			if (m_isPlaced)
			{
				// move
				if (command->IsMove())
				{
					if (Move()) {
						result = CCommandApplyResult::OK;
					}
					else
					{
						result = CCommandApplyResult::IGNORE_FALL_OFF_MOVE;
					}
				}
				else
				{
					result = CCommandApplyResult::OK;
				}

				// rotate
				Rotate(command->GetRotate());

				// report
				if (command->DoReport()) {
					std::cout
						<< m_position.x << ","
						<< m_position.y << ","
						<< DirectionToString(m_direction) << std::endl;
				}
			}
			else
			{
				result = CCommandApplyResult::ROBOT_NOT_YET_PLACED;
			}
		}
	}

	return result;
}
