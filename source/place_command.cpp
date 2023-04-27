#include "place_command.hpp"

const string PlaceCommand::PATTERN = "^\\s*(PLACE)\\s+([0-9])+\\s*,\\s*([0-9]+)\\s*,\\s*(NORTH|SOUTH|EAST|WEST)\\s*$";

PlaceCommand::PlaceCommand(RobotPosition& robotPosition):
    robotPosition(robotPosition)
{
    
}

void PlaceCommand::Execute(Robot& robot, Table& table)
{
    robot.Place(robotPosition, table);
}

RobotPosition& PlaceCommand::GetRobotPosition()
{
    return robotPosition;
}