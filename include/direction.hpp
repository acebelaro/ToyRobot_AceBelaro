#pragma once

#include <string>

using namespace std;

// ordered clockwise so that rotate right and rotate left can be
// as easy as incrementing and decrementing, respectively.
// watch out for end points
enum class Direction {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

#define MIN_DIR static_cast<int>(Direction::NORTH)
#define MAX_DIR	static_cast<int>(Direction::WEST)

Direction StringToDirection(string);
const char * DirectionToString(Direction);
