#pragma once
#include <iobserver.h>

class FileLogger final : public IObserver
{
public:
    ~FileLogger() override = default;
    void onBlockReady(const Block &block) override;
};
