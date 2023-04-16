
#include "direction.hpp"
#include <map>

static map<Direction,const char *> stringToDirectionMap = {
	{Direction::NORTH,"NORTH"},
	{Direction::EAST,"EAST"},
	{Direction::SOUTH,"SOUTH"},
	{Direction::WEST,"WEST"}
};

Direction StringToDirection(string directionStr)
{
	Direction direction = Direction::NORTH;
	for( auto & it: stringToDirectionMap )
	{
		if( directionStr.compare(it.second) == 0 )
		{
			direction = it.first;
			break;
		}
	}
	return direction;
}

const char * DirectionToString(Direction direction)
{
	for( auto & it: stringToDirectionMap )
	{
		if( it.first == direction )
		{
			return it.second;
		}
	}

	return nullptr;
}