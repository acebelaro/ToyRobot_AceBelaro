//******************************************************************************
/*! @file       RobotPosition.hpp
	@brief      External interface of Robot Position class
*/
//******************************************************************************
#pragma once

#include "coordinate.hpp"
#include "direction.hpp"

//******************************************************************************
//               Public definitions
//******************************************************************************

class RobotPosition
{
    public:
        RobotPosition(const Coordinate&, Direction);
        ~RobotPosition() = default;

    private:
        Coordinate _coordinate;
        Direction _direction;

    public:
        const Coordinate& GetCoordinate() const;
        void SetCoordinate(Coordinate&);
        Direction GetDirection() const;
        void SetDirection(Direction);
};
