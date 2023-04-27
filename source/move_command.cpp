#include "move_command.hpp"

const string MoveCommand::PATTERN = "^\\s*MOVE\\s*$";

void MoveCommand::Execute(Robot& robot, Table& table)
{
    robot.Move(table);
}