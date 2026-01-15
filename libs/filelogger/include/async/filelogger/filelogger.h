#pragma once
#include "fileworker.h"

namespace async::filelogger {

    class FileLogger {
    public:
        FileLogger();
        ~FileLogger();

        void push(async::defs::Block);
        void stop();

    private:
        async::common::BlockingQueue<async::defs::Block> m_queue;
        FileWorker m_w1;
        FileWorker m_w2;
    };

}
