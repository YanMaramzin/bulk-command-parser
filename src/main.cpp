#include <iostream>

#include <filelogger.h>
#include <consolelogger.h>
#include <blockcontroller.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;

    const std::size_t N = std::stoul(argv[1]);

    BlockController controller(N);

    const auto fileLogger = std::make_shared<FileLogger>();
    const auto consoleLogger = std::make_shared<ConsoleLogger>();

    controller.subscribe(fileLogger);
    controller.subscribe(consoleLogger);

    std::string line;
    while (std::getline(std::cin, line))
        controller.procesLine(line);

    controller.processEOF();
}

