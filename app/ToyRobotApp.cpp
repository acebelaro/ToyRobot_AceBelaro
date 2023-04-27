#include "ToyRobotApp.hpp"
#include "command_parser.hpp"
#include <string>
#include <iostream>

//******************************************************************************
//               Private macros
//******************************************************************************

#define TABLE_WIDTH		( 5 )	/* table width */
#define TABLE_HEIGHT	( 5 )	/* table height */

#define NORTH_AVATAR	( "^" )	/* avatar for robot facing NORTH */
#define EAST_AVATAR		( ">" )	/* avatar for robot facing EAST */
#define SOUTH_AVATAR	( "v" )	/* avatar for robot facing SOUTH */
#define WEST_AVATAR		( "<" )	/* avatar for robot facing WEST */

//******************************************************************************
//               Class function definition
//******************************************************************************

CToyRobotApp::CToyRobotApp():
	_table(TABLE_WIDTH, TABLE_HEIGHT)
{

}

void CToyRobotApp::PrintTable()
{
	string toPrint = " * ";
	Coordinate coordinate = _robot.GetCoordinate();
	int height = _table.GetHeight();
	int width = _table.GetWidth();
	for(int h = height - 1; h >= 0; h--)
	{
		for(int w = 0; w < width; w++)
		{
			toPrint = " * ";
			if (_robot.IsPlaced())
			{
				if (coordinate.GetX() == w && coordinate.GetY() == h)
				{
					switch (_robot.GetDirection())
					{
					case Direction::NORTH:
						toPrint = NORTH_AVATAR;
						break;
					case Direction::EAST:
						toPrint = EAST_AVATAR;
						break;
					case Direction::SOUTH:
						toPrint = SOUTH_AVATAR;
						break;
					case Direction::WEST:
						toPrint = WEST_AVATAR;
						break;
					default:
						break;
					}
					// normalize
					toPrint = string(" ") + 
						toPrint + 
						string(" ");
				}
			}
			cout << toPrint;
		}
		cout << endl;
	}
}

void CToyRobotApp::Play()
{
	CommandParser commandParser;
	string input;

	while (true) {
		PrintTable();
		cout << "Enter Command (x to exit): ";
		getline(cin, input);
		if ("x" == input)
		{
			break;
		}
		else 
		{
			UPTR_COMMAND cmd;
			commandParser.parseCommand(input,cmd);
			if( cmd != nullptr )
			{
				cmd->Execute(_robot,_table);
				cout << endl;
			}
		}
	}
}

//******************************************************************************
//               Public function definition
//******************************************************************************

int main() {

	CToyRobotApp app;

	app.Play();

	return 0;
}
