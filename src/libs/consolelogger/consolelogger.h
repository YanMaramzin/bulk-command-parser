#pragma once
#include <iobserver.h>

class ConsoleLogger final : public IObserver
{
public:
    void onBlockReady(const Block &block) override;
};
