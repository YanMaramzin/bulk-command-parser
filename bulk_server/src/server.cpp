#include "bulk_server/server.h"
#include <boost/asio.hpp>
#include <boost/asio/strand.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <memory>
#include <async/consolelogger/consoleworker.h>
#include <async/filelogger/filelogger.h>
#include "bulk_server/session.h"

namespace bulk_server {

    Server::Server(unsigned short port, std::size_t bulk_size)
        : io_context_(),
          acceptor_(io_context_, {boost::asio::ip::tcp::v4(), port}),
          bulk_size_(bulk_size)
    {
        // общий контроллер для статических блоков (разделяемый между клиентами)
        static_block = std::make_shared<async::blockcontroller::BlockController>(bulk_size_);
        dispatcher = std::make_shared<async::dispatcher::Dispatcher>();
        static_block->subscribe(dispatcher);
    }

    void Server::run() {
        do_accept();
        io_context_.run();
    }

    void Server::do_accept() {
        auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
        acceptor_.async_accept(*socket, [this, socket](boost::system::error_code ec){
            if (!ec) {
                // создаём сессию для клиента
                auto session = std::make_shared<Session>(socket, static_block, dispatcher, bulk_size_);
                sessions_.push_back(session);
                session->start();
            }
            do_accept(); // продолжить принимать новые подключения
        });
    }

}
