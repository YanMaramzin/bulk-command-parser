#include <fstream>
#include "filelogger.h"

void FileLogger::onBlockReady(const Block &block) {

    using namespace std::chrono;

    const auto seconds =
            duration_cast<std::chrono::seconds>(
                block.timestamp.time_since_epoch()
            ).count();

    const std::string filename =
            "bulk" + std::to_string(seconds) + ".log";

    std::ofstream out(filename);
    for (const auto &cmd : block.commands)
        out << cmd << '\n';
}
