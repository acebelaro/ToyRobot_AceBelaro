//******************************************************************************
/*! @file       table.cpp
	@brief      Source definition for table
*/
//******************************************************************************
#include "table.hpp"

//******************************************************************************
//               Class function definition
//******************************************************************************

CTable::CTable(int width, int height)
{
	if (0 <= width && 0 <= height)
	{
		m_width = width;
		m_height = height;
	}
	else
	{
		throw TableInvalidSizeException();
	}
}

CTable::~CTable()
{
	// Do nothing
}

int CTable::GetWidth() {
	return m_width;
}

int CTable::GetHeight() {
	return m_height;
}

bool CTable::IsPositionAllowed(stPosition const* position)
{
	bool allowed = false;
	int x = position->x;
	int y = position->y;
	if (x >= 0 && 
		y >= 0 &&
		x < m_width && 
		y < m_height) {
		allowed = true;
	}
	return allowed;
}
