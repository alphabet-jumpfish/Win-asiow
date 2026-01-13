#ifndef CLIENT_H
#define CLIENT_H

#include <asio.hpp>
#include <string>

class Client {
public:
    Client(asio::io_context& io_context,
           const std::string& host,
           const std::string& port);

    void sendRequest(const std::string& message);
    std::string getResponse() const;

private:
    asio::ip::tcp::socket socket_;
    std::string response_;
};

#endif // CLIENT_H
