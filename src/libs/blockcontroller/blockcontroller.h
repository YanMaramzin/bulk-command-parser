#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iobserver.h>

#include "../defs/block.h"

class BlockController
{
public:
    explicit BlockController(std::size_t staticBlockSize);
    void subscribe(const std::shared_ptr<IObserver> &observer);

    void procesLine(const std::string &line);
    void processEOF();

private:
    void flushBlock();
    void startBlockIfNeeded();

    std::size_t m_staticBlockSize {0};
    std::vector<std::weak_ptr<IObserver>> m_subscribers;

    Block m_currentBlock;

    bool m_dynamicMode {false};
    std::size_t m_dynamicBlockDepth {0};
};
