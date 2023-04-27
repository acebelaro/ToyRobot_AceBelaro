#include "command.hpp"

class ReportCommand : public Command
{
    public:
        static const string PATTERN;

        ReportCommand() = default;
        ~ReportCommand() = default;

        void Execute(Robot&, Table&) override;
};
