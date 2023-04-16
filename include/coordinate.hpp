//******************************************************************************
/*! @file       coordinate.hpp
	@brief      External interface of Coordinate class
*/
//******************************************************************************
#pragma once

//******************************************************************************
//               Public definitions
//******************************************************************************

class Coordinate
{
    public:
        Coordinate(int,int);
        ~Coordinate() = default;

    private:
        int _x;
        int _y;

    public:
        int GetX() const;
        int GetY() const;
        void SetX(int);
        void SetY(int);
};
