#include "command.hpp"
#include "RobotPosition.hpp"

class PlaceCommand : public Command
{
    public:
        static const string PATTERN;

        PlaceCommand(RobotPosition&);
        ~PlaceCommand() = default;

        void Execute(Robot&, Table&) override;

        RobotPosition& GetRobotPosition();

    private:
        RobotPosition robotPosition;
};
