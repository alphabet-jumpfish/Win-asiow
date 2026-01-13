//
// Created by wangjiawen on 2026/1/14.
//

#include "AsioLocalServer.h"
#include "controller/HelloController.h"
#include <iostream>
#include <sstream>

AsioLocalServer::AsioLocalServer(unsigned short port)
    : acceptor_(io_context_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
    , controller_(std::make_unique<HelloController>())
    , running_(false) {
    std::cout << "Server initialized on port " << port << std::endl;
}

AsioLocalServer::~AsioLocalServer() {
    stop();
}

void AsioLocalServer::run() {
    running_ = true;
    std::cout << "Server starting..." << std::endl;
    startAccept();
    io_context_.run();
}

void AsioLocalServer::stop() {
    if (running_) {
        running_ = false;
        io_context_.stop();
        std::cout << "Server stopped" << std::endl;
    }
}

void AsioLocalServer::startAccept() {
    auto socket = std::make_shared<asio::ip::tcp::socket>(io_context_);

    acceptor_.async_accept(*socket, [this, socket](const asio::error_code& error) {
        handleAccept(socket, error);
    });
}

void AsioLocalServer::handleAccept(std::shared_ptr<asio::ip::tcp::socket> socket, const asio::error_code& error) {
    if (!error) {
        std::cout << "Client connected" << std::endl;
        handleClient(socket);
    } else {
        std::cerr << "Accept error: " << error.message() << std::endl;
    }

    if (running_) {
        startAccept();
    }
}

void AsioLocalServer::handleClient(std::shared_ptr<asio::ip::tcp::socket> socket) {
    try {
        asio::streambuf buffer;
        asio::read_until(*socket, buffer, "\r\n\r\n");

        std::istream request_stream(&buffer);
        std::string request_line;
        std::getline(request_stream, request_line);

        std::cout << "Request: " << request_line << std::endl;

        std::string response_body = parseRequest(request_line);

        std::ostringstream response;
        response << "HTTP/1.1 200 OK\r\n";
        response << "Content-Type: text/plain\r\n";
        response << "Content-Length: " << response_body.length() << "\r\n";
        response << "Connection: close\r\n";
        response << "\r\n";
        response << response_body;

        asio::write(*socket, asio::buffer(response.str()));
        socket->close();
    } catch (std::exception& e) {
        std::cerr << "Error handling client: " << e.what() << std::endl;
    }
}

std::string AsioLocalServer::parseRequest(const std::string& request) {
    std::istringstream iss(request);
    std::string method, path, version;
    iss >> method >> path >> version;

    if (path.find("/hello") == 0) {
        std::string name;
        size_t query_pos = path.find('?');
        if (query_pos != std::string::npos) {
            std::string query = path.substr(query_pos + 1);
            size_t name_pos = query.find("name=");
            if (name_pos != std::string::npos) {
                name = query.substr(name_pos + 5);
            }
        }
        return controller_->handleHello(name);
    }

    return "404 Not Found";
}