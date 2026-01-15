#include "async/blockcontroller/blockcontroller.h"
#include <async/defs/timestamp.h>

namespace async::blockcontroller {

    BlockController::BlockController(std::size_t size)
        : m_block_size(size) {}

    void BlockController::subscribe(std::weak_ptr<async::sinks::IBlockSink> sink) {
        m_sinks.push_back(std::move(sink));
    }

    void BlockController::on_command(const async::defs::Command& cmd) {
        m_current.push_back(cmd);
        if (m_current.size() == m_block_size)
            flush();
    }

    void BlockController::on_eof() {
        if (!m_current.empty())
            flush();
    }

    void BlockController::flush() {
        async::defs::Block block{
            .commands = std::move(m_current),
            .timestamp = async::defs::now()
        };
        m_current.clear();

        for (auto it = m_sinks.begin(); it != m_sinks.end();) {
            if (auto s = it->lock()) {
                s->consume(block);
                ++it;
            } else {
                it = m_sinks.erase(it);
            }
        }
    }

}
