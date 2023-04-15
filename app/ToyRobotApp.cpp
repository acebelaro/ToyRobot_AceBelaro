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

CToyRobotApp::CToyRobotApp()
{
	m_table = new CTable(TABLE_WIDTH, TABLE_HEIGHT);
	m_robot = new CRobot(m_table);
}

CToyRobotApp::~CToyRobotApp()
{
	delete m_robot;
	delete m_table;
}

void CToyRobotApp::PrintTable()
{
	std::string toPrint = " * ";
	stPosition position = m_robot->GetPosition();
	int height = m_table->GetHeight();
	int width = m_table->GetWidth();
	for (int h = height - 1; h >= 0; h--)
	{
		for (int w = 0; w < width; w++)
		{
			toPrint = " * ";

			if (m_robot->IsPlaced())
			{
				if (position.x == w && position.y == h)
				{
					switch (m_robot->GetDirection())
					{
					case CDirection::NORTH:
						toPrint = NORTH_AVATAR;
						break;
					case CDirection::EAST:
						toPrint = EAST_AVATAR;
						break;
					case CDirection::SOUTH:
						toPrint = SOUTH_AVATAR;
						break;
					case CDirection::WEST:
						toPrint = WEST_AVATAR;
						break;
					default:
						break;
					}
					// normalize
					toPrint = std::string(" ") + 
						toPrint + 
						std::string(" ");
				}
			}

			std::cout << toPrint;
		}
		std::cout << std::endl;
	}
}

void CToyRobotApp::Play()
{
	CCommandParser commandParser;
	std::string input;
	CCommand* command;
	CCommandApplyResult result;

	while (true) {
		PrintTable();
		std::cout << "Enter Command (x to exit): ";
		std::getline(std::cin, input);
		if ("x" == input)
		{
			break;
		}
		else 
		{
			try {
				command = commandParser.ParseCommand(input);
				if (nullptr != command)
				{
					result = m_robot->ApplyCommand(command);
					switch (result)
					{
					case CCommandApplyResult::OK:
						break;
					case CCommandApplyResult::ERROR:
						break;
					case CCommandApplyResult::ROBOT_NOT_YET_PLACED:
						std::cout << "Place robot first!" << std::endl;
						break;
					case CCommandApplyResult::INVALID_PLACE:
						std::cout << "Invalid place position!" << std::endl;
						break;
					case CCommandApplyResult::IGNORE_FALL_OFF_MOVE:
						std::cout << "Robot ignored move due to falling off!" << std::endl;
						break;
					default:
						break;
					}
					delete command;
				}
			}
			catch (ParserCommandException& e)
			{
				std::cout << std::string(e.what()) << std::endl;
			}
			catch (std::exception& e)
			{
				std::cout << "Unknown error " << std::string(e.what()) << std::endl;
				std::cout << "Ending game..." << std::endl;
				break;
			}

			std::cout << std::endl;
		}
	}
}

//******************************************************************************
//               Public function definition
//******************************************************************************

int main() {

	CToyRobotApp app;

	app.Play();

	return 1;
}
