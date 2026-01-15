#include "async/consolelogger/consoleworker.h"
#include <iostream>

namespace async::consolelogger {

    ConsoleWorker::ConsoleWorker()
        : m_thread(&ConsoleWorker::run, this) {}

    ConsoleWorker::~ConsoleWorker() {
        stop();
    }

    void ConsoleWorker::push(async::defs::Block block) {
        m_queue.push(std::move(block));
    }

    void ConsoleWorker::stop() {
        if (!m_running.exchange(false)) return;
        m_queue.stop();
        if (m_thread.joinable())
            m_thread.join();
    }

    void ConsoleWorker::run() {
        while (m_running) {
            auto item = m_queue.pop();
            if (!item) break;

            std::cout << "bulk:";
            for (auto& c : item->commands)
                std::cout << " " << c;
            std::cout << std::endl;
        }
    }

}
