#pragma once 

// ID for UI

#define ID_TILE_BUTTON_MIN	( 3000 )
#define TILE_BUTTON_COUNT	( 100 )	// allowed tile count
									// (width x height should not exceed this value

enum
{
	ID_COMMAND_INPUT = 2000,
	ID_COMMAND_RESPONSE,
	ID_TILE_BUTTON = ID_TILE_BUTTON_MIN,
	ID_TILE_BUTTON_MAX = ID_TILE_BUTTON + TILE_BUTTON_COUNT
};