#pragma once
#include <block.h>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onBlockReady(const Block &block) = 0;
};
