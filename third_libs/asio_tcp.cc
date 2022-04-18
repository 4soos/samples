#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;

void on_connect(system::error_code error_code) {
    if (error_code)
        cout << "async conn_socket" << error_code.message() << endl;
    else
        cout << "aysnc conn_socket ok" << endl;
}

int main() {
    asio::io_service ios;
    asio::ip::tcp::endpoint addr(
            asio::ip::address::from_string("127.0.0.1"),
            12345
        );

    asio::ip::tcp::socket conn_socket(ios);
    conn_socket.async_connect(addr, &conn_socket);
    ios.run();

    return 0;
}

