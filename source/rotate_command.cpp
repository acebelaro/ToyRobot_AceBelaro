#include "rotate_command.hpp"

const string RotateCommand::PATTERN = "^\\s*(LEFT|RIGHT)\\s*$";

RotateCommand::RotateCommand(Rotate rotate):
    rotate(rotate)
{

}

void RotateCommand::Execute(Robot& robot, Table& table)
{
    if( Rotate::LEFT == rotate)
    {
        robot.RotateLeft();
    }
    else if( Rotate::RIGHT == rotate )
    {
        robot.RotateRight();
    }
}

Rotate RotateCommand::GetRotate()
{
    return rotate;
}