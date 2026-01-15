#pragma once
#include <thread>
#include <atomic>
#include <string>
#include <async/common/blockingqueue.h>
#include <async/defs/block.h>

namespace async::filelogger {

    class FileWorker {
    public:
        FileWorker(async::common::BlockingQueue<async::defs::Block>&, std::string);
        ~FileWorker();

        void stop();

    private:
        void run();
        std::string filename(const async::defs::Block&) const;

        async::common::BlockingQueue<async::defs::Block>& m_queue;
        std::string m_suffix;
        std::thread m_thread;
        std::atomic<bool> m_running{true};
    };

}
