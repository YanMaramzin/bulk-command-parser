#include "async/dispatcher/dispatcher.h"

namespace async::dispatcher {

    Dispatcher::Dispatcher()
        : m_console(std::make_unique<async::consolelogger::ConsoleWorker>()),
          m_files(std::make_unique<async::filelogger::FileLogger>()) {}

    Dispatcher::~Dispatcher() {
        stop();
    }

    void Dispatcher::consume(const async::defs::Block& block) {
        m_console->push(block);
        m_files->push(block);
    }

    void Dispatcher::stop() {
        if (m_console) m_console->stop();
        if (m_files) m_files->stop();
    }

}
