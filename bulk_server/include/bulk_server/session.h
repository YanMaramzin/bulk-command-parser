#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <async/blockcontroller/blockcontroller.h>
#include <async/dispatcher/dispatcher.h>

namespace bulk_server {

    class Session : public std::enable_shared_from_this<Session> {
    public:
        Session(std::shared_ptr<boost::asio::ip::tcp::socket> socket,
                std::shared_ptr<async::blockcontroller::BlockController> static_block,
                std::shared_ptr<async::dispatcher::Dispatcher> dispatcher,
                std::size_t bulk_size);
        void start();

    private:
        void do_read();

        std::shared_ptr<boost::asio::ip::tcp::socket> socket_;
        enum { max_length = 1024 };
        char data_[max_length];

        std::string buffer_;
        std::size_t bulk_size_;

        std::shared_ptr<async::blockcontroller::BlockController> static_block_;
        std::shared_ptr<async::dispatcher::Dispatcher> dispatcher_;

        // динамический блок для этого клиента
        std::unique_ptr<async::blockcontroller::BlockController> dynamic_block_;
        bool in_dynamic_block_{false};
    };

}
