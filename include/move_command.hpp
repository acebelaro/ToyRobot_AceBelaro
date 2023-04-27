#include "command.hpp"

class MoveCommand : public Command
{
    public:
        static const string PATTERN;

        MoveCommand() = default;
        ~MoveCommand() = default;

        void Execute(Robot&, Table&) override;
};
