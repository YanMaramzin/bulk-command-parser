#pragma once
#include <memory>
#include <async/sinks/iblock_sink.h>
#include <async/consolelogger/consoleworker.h>
#include <async/filelogger/filelogger.h>

namespace async::dispatcher {

    class Dispatcher : public async::sinks::IBlockSink {
    public:
        Dispatcher();
        ~Dispatcher();

        void consume(const async::defs::Block&) override;
        void stop();

    private:
        std::unique_ptr<async::consolelogger::ConsoleWorker> m_console;
        std::unique_ptr<async::filelogger::FileLogger> m_files;
    };

}
