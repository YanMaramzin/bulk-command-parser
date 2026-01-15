#pragma once
#include <vector>
#include <memory>
#include <async/defs/command.h>
#include <async/defs/block.h>
#include <async/sinks/iblock_sink.h>

namespace async::blockcontroller {

    class BlockController {
    public:
        explicit BlockController(std::size_t block_size);

        void subscribe(std::weak_ptr<async::sinks::IBlockSink>);
        void on_command(const async::defs::Command&);
        void on_eof();

    private:
        void flush();

        std::size_t m_block_size;
        std::vector<async::defs::Command> m_current;
        std::vector<std::weak_ptr<async::sinks::IBlockSink>> m_sinks;
    };

}
