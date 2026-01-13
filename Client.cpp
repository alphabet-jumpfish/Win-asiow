#include "Client.h"
#include <iostream>
#include <vector>

Client::Client(asio::io_context& io_context,
               const std::string& host,
               const std::string& port)
    : io_context_(io_context),
      socket_(io_context),
      host_(host),
      port_(port) {
    reconnect();
}

void Client::sendRequest(const std::string& message) {
    // 每次请求前都重新连接（因为服务器会在响应后关闭连接）
    reconnect();

    asio::write(socket_, asio::buffer(message));
    std::cout << "已发送: " << message << std::endl;

    std::vector<char> buffer(1024);
    asio::error_code error;
    size_t len = socket_.read_some(asio::buffer(buffer), error);

    if (error == asio::error::eof) {
        std::cout << "服务器关闭连接" << std::endl;
    } else if (error) {
        throw asio::system_error(error);
    }

    response_ = std::string(buffer.data(), len);
    std::cout << "收到响应: " << response_ << std::endl;
}

std::string Client::getResponse() const {
    return response_;
}

void Client::reconnect() {
    if (socket_.is_open()) {
        socket_.close();
    }

    asio::ip::tcp::resolver resolver(io_context_);
    auto endpoints = resolver.resolve(host_, port_);

    asio::connect(socket_, endpoints);
    std::cout << "已连接到服务器 " << host_ << ":" << port_ << std::endl;
}
