//
// Created by wangjiawen on 2026/1/14.
//

#ifndef ASIOW_ASIOLOCALSERVER_H
#define ASIOW_ASIOLOCALSERVER_H

#include <asio.hpp>
#include <memory>
#include <string>

class HelloController;

class AsioLocalServer {
public:
    AsioLocalServer(unsigned short port);
    ~AsioLocalServer();

    void run();
    void stop();

private:
    void startAccept();
    void handleAccept(std::shared_ptr<asio::ip::tcp::socket> socket, const asio::error_code& error);
    void handleClient(std::shared_ptr<asio::ip::tcp::socket> socket);
    std::string parseRequest(const std::string& request);

    asio::io_context io_context_;
    asio::ip::tcp::acceptor acceptor_;
    std::unique_ptr<HelloController> controller_;
    bool running_;
};

#endif //ASIOW_ASIOLOCALSERVER_H