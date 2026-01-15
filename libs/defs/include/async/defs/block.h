#pragma once
#include <vector>
#include "command.h"
#include "timestamp.h"

namespace async::defs {

    struct Block {
        std::vector<Command> commands;
        TimePoint timestamp;
    };

}
