#include "../include/async/filelogger/fileworker.h"
#include <fstream>
#include <chrono>

namespace async::filelogger {

    FileWorker::FileWorker(async::common::BlockingQueue<async::defs::Block>& q,
                           std::string s)
        : m_queue(q), m_suffix(std::move(s)),
          m_thread(&FileWorker::run, this) {}

    FileWorker::~FileWorker() {
        stop();
    }

    void FileWorker::stop() {
        if (!m_running.exchange(false)) return;
        if (m_thread.joinable())
            m_thread.join();
    }

    std::string FileWorker::filename(const async::defs::Block& b) const {
        using namespace std::chrono;
        auto ts = duration_cast<seconds>(
            b.timestamp.time_since_epoch()).count();
        return "bulk" + std::to_string(ts) + "_" + m_suffix + ".log";
    }

    void FileWorker::run() {
        while (m_running) {
            auto item = m_queue.pop();
            if (!item) break;

            std::ofstream f(filename(*item));
            for (auto& c : item->commands)
                f << c << '\n';
        }
    }

}
