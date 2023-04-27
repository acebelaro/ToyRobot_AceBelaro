#pragma once

#include <memory>
#include "robot.hpp"
#include "table.hpp"

using namespace std;

class Command
{
    public:
        Command() = default;
        virtual ~Command() = default;
        virtual void Execute(Robot&, Table&) = 0;
};

typedef unique_ptr<Command> UPTR_COMMAND;