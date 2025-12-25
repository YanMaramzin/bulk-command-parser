#include <iostream>
#include "blockcontroller.h"

BlockController::BlockController(std::size_t staticBlockSize)
    : m_staticBlockSize(staticBlockSize)
{
}

void BlockController::subscribe(const std::shared_ptr<IObserver> &observer)
{
    m_subscribers.emplace_back(observer);
}

void BlockController::procesLine(const std::string &line) {

    if (line.empty())
        return;

    if (line == "{") {
        if (!m_dynamicMode) {
            flushBlock();
            m_dynamicMode = true;
            m_dynamicBlockDepth = 1;
        } else {
            ++m_dynamicBlockDepth;
        }
        return;
    }

    if (line == "}")
    {
        if (m_dynamicMode && --m_dynamicBlockDepth == 0)
        {
            flushBlock();
            m_dynamicMode = false;
        }
        return;
    }

    startBlockIfNeeded();
    m_currentBlock.commands.push_back(line);

    if (!m_dynamicMode &&
        m_currentBlock.commands.size() == m_staticBlockSize)
        flushBlock();
}

void BlockController::processEOF()
{
    if (!m_dynamicMode)
        flushBlock();
}

void BlockController::flushBlock()
{
    if (m_currentBlock.commands.empty())
        return;

    for (auto &s : m_subscribers)
        if (const auto l = s.lock())
            l->onBlockReady(m_currentBlock);

    m_currentBlock = {};
}

void BlockController::startBlockIfNeeded()
{
    if (m_currentBlock.commands.empty())
        m_currentBlock.timestamp = std::chrono::system_clock::now();
}
