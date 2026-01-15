#include "async/filelogger/filelogger.h"

namespace async::filelogger {

    FileLogger::FileLogger()
        : m_w1(m_queue, "1"), m_w2(m_queue, "2") {}

    FileLogger::~FileLogger() {
        stop();
    }

    void FileLogger::push(async::defs::Block block) {
        m_queue.push(std::move(block));
    }

    void FileLogger::stop() {
        m_queue.stop();
        m_w1.stop();
        m_w2.stop();
    }

}
