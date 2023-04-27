#include "command.hpp"

enum class Rotate {
	LEFT,
    RIGHT
};

class RotateCommand : public Command
{
    public:
        static const string PATTERN;

        RotateCommand(Rotate);
        ~RotateCommand() = default;

        void Execute(Robot&, Table&) override;
        Rotate GetRotate();
    private:
        Rotate rotate;
};
