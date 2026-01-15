#include "bulk_server/server.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: bulk_server <port> <bulk_size>\n";
        return 1;
    }

    unsigned short port = static_cast<unsigned short>(std::atoi(argv[1]));
    std::size_t bulk_size = std::stoul(argv[2]);

    try {
        bulk_server::Server server(port, bulk_size);
        server.run(); // блокирует поток, пока сервер работает
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 2;
    }
}
