#include "consolelogger.h"
#include <iostream>

void ConsoleLogger::onBlockReady(const Block &block)
{
    std::cout << "bulk:";
    for (std::size_t i = 0; i < block.commands.size(); ++i)
        std::cout << (i == 0 ? " " : ", ") << block.commands[i];

    std::cout << '\n';

}
