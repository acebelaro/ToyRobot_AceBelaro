#pragma once 

// ID for UI

#define ID_TILE_BUTTON_MIN	( 3000 )
#define TILE_BUTTON_COUNT	( 100 )	// allowed tile count
									// (width x height should not exceed this value

enum
{
	// Toy Robot Dialog
	ID_COMMAND_INPUT = 2000,
	ID_COMMAND_RESPONSE,
	ID_TILE_BUTTON = ID_TILE_BUTTON_MIN,
	ID_TILE_BUTTON_MAX = ID_TILE_BUTTON + TILE_BUTTON_COUNT,

	// Board Setup Dialog
	ID_BOARD_SETUP_WIDTH_LABEL,
	ID_BOARD_SETUP_WIDTH_EDIT,
	ID_BOARD_SETUP_HEIGHT_LABEL,
	ID_BOARD_SETUP_HEIGHT_EDIT,
	ID_BOARD_SETUP_OK_BUTTON
};