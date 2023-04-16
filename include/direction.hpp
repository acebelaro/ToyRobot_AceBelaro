#pragma once

#include <string>

using namespace std;

enum class Direction {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

Direction StringToDirection(string);
const char * DirectionToString(Direction);
