#include <async/async.h>

int main() {
    auto h = async::connect(3);
    async::receive(h, "cmd1\ncmd2\ncmd3\ncmd4\n", 20);
    async::disconnect(h);
}
