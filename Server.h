#ifndef SERVER_H
#define SERVER_H

#include <asio.hpp>
#include <memory>
#include <string>

class HelloController;

class Server {
public:
    Server(asio::io_context& io_context, unsigned short port);
    ~Server();

private:
    void startAccept();
    void handleAccept(std::shared_ptr<asio::ip::tcp::socket> socket,
                      const asio::error_code& error);
    void handleClient(std::shared_ptr<asio::ip::tcp::socket> socket);

    asio::ip::tcp::acceptor acceptor_;
    std::unique_ptr<HelloController> controller_;
};

#endif // SERVER_H
