#pragma once
#include <async/defs/block.h>

namespace async::sinks {

    class IBlockSink {
    public:
        virtual ~IBlockSink() = default;
        virtual void consume(const async::defs::Block& block) = 0;
    };

}
