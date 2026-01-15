#include "async/async.h"
#include <string>
#include <async/blockcontroller/blockcontroller.h>
#include <async/dispatcher/dispatcher.h>

namespace async {

    struct Context {
        async::blockcontroller::BlockController controller;
        std::shared_ptr<async::dispatcher::Dispatcher> dispatcher;
        std::string buffer;

        explicit Context(std::size_t n)
            : controller(n),
              dispatcher(std::make_shared<async::dispatcher::Dispatcher>()) {
            controller.subscribe(dispatcher);
        }
    };

    void* connect(std::size_t bulk_size) {
        return new Context{bulk_size};
    }

    void receive(void* h, const char* data, std::size_t size) {
        auto* ctx = static_cast<Context*>(h);
        ctx->buffer.append(data, size);

        std::size_t pos;
        while ((pos = ctx->buffer.find('\n')) != std::string::npos) {
            auto line = ctx->buffer.substr(0, pos);
            ctx->buffer.erase(0, pos + 1);
            ctx->controller.on_command(line);
        }
    }

    void disconnect(void* h) {
        auto* ctx = static_cast<Context*>(h);

        if (!ctx->buffer.empty())
            ctx->controller.on_command(ctx->buffer);

        ctx->controller.on_eof();
        ctx->dispatcher->stop();
        delete ctx;
    }

}
