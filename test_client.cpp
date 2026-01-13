#include <asio.hpp>
#include <iostream>
#include "Client.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    // 强制 Windows 控制台使用 UTF-8
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    try {
        asio::io_context io;

        // 连接到本地服务器的 8080 端口
        Client client(io, "localhost", "8080");

        // 发送测试请求
        std::cout << "\n=== 测试 1: 发送 'World' ===" << std::endl;
        client.sendRequest("World");

        // std::cout << "\n=== 测试 2: 发送 'ASIO' ===" << std::endl;
        // client.sendRequest("ASIO");

        std::cout << "\n=== 测试 3: 发送 'Claude' ===" << std::endl;
        client.sendRequest("Claude");

    } catch (std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
    }

    return 0;
}
