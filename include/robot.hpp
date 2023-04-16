//******************************************************************************
/*! @file       robot.hpp
	@brief      External interface of robot class
*/
//******************************************************************************
#pragma once

#include <memory>
#include "RobotPosition.hpp"
#include "direction.hpp"
#include "table.hpp"

using namespace std;

//******************************************************************************
//               Public definitions
//******************************************************************************

class Robot
{
	public:
		Robot();
		~Robot() = default;

	private:
		bool m_isPlaced;
		unique_ptr<RobotPosition> _position;
		
	public:
		void Place(const RobotPosition&, const Table&);
		void RotateLeft();
		void RotateRight();
		bool Move(const Table&);
		string Report() const;
		bool IsPlaced() const;
		Direction GetDirection() const;
		Coordinate GetCoordinate() const;
};
