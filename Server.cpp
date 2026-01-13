#include "Server.h"
#include "controller/HelloController.h"
#include <iostream>
#include <vector>

Server::Server(asio::io_context& io_context, unsigned short port)
    : acceptor_(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)),
      controller_(std::make_unique<HelloController>()) {
    std::cout << "服务器启动在端口: " << port << std::endl;
    startAccept();
}

Server::~Server() = default;

void Server::startAccept() {
    auto socket = std::make_shared<asio::ip::tcp::socket>(acceptor_.get_executor());

    acceptor_.async_accept(*socket,
        [this, socket](const asio::error_code& error) {
            handleAccept(socket, error);
        });
}

void Server::handleAccept(std::shared_ptr<asio::ip::tcp::socket> socket,
                          const asio::error_code& error) {
    if (!error) {
        std::cout << "新客户端连接: " << socket->remote_endpoint() << std::endl;
        handleClient(socket);
    } else {
        std::cerr << "接受连接错误: " << error.message() << std::endl;
    }

    // 继续接受新连接
    startAccept();
}

void Server::handleClient(std::shared_ptr<asio::ip::tcp::socket> socket) {
    auto buffer = std::make_shared<std::vector<char>>(1024);

    socket->async_read_some(asio::buffer(*buffer),
        [this, socket, buffer](const asio::error_code& error, std::size_t bytes_transferred) {
            if (!error) {
                std::string request(buffer->data(), bytes_transferred);
                std::cout << "收到请求: " << request << std::endl;

                // 使用 controller 处理请求
                std::string response = controller_->handleHello(request);

                // 发送响应
                asio::async_write(*socket, asio::buffer(response),
                    [socket](const asio::error_code& error, std::size_t) {
                        if (error) {
                            std::cerr << "发送响应错误: " << error.message() << std::endl;
                        }
                        socket->close();
                    });
            } else {
                std::cerr << "读取数据错误: " << error.message() << std::endl;
            }
        });
}
