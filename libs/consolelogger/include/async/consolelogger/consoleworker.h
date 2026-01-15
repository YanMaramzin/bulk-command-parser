#pragma once
#include <thread>
#include <atomic>
#include <async/common/blockingqueue.h>
#include <async/defs/block.h>

namespace async::consolelogger {

    class ConsoleWorker {
    public:
        ConsoleWorker();
        ~ConsoleWorker();

        void push(async::defs::Block);
        void stop();

    private:
        void run();

        async::common::BlockingQueue<async::defs::Block> m_queue;
        std::thread m_thread;
        std::atomic<bool> m_running{true};
    };

}
