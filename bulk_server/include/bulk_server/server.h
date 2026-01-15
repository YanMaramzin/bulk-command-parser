#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <vector>
#include <string>
#include <async/blockcontroller/blockcontroller.h>
#include <async/dispatcher/dispatcher.h>

namespace bulk_server {

    class Session;

    class Server {
    public:
        Server(unsigned short port, std::size_t bulk_size);
        void run();

    private:
        void do_accept();

        boost::asio::io_context io_context_;
        boost::asio::ip::tcp::acceptor acceptor_;
        std::vector<std::shared_ptr<Session>> sessions_;

        std::shared_ptr<async::blockcontroller::BlockController> static_block;
        std::shared_ptr<async::dispatcher::Dispatcher> dispatcher;

        std::size_t bulk_size_;
    };

}
