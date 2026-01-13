#include <asio.hpp>
#include <iostream>

#ifdef _WIN32
#include <windows.h> // 必须包含这个头文件
#endif

int main() {
    // 强制 Windows 控制台使用 UTF-8 (代码页 65001)
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    asio::io_context io;
    std::cout << "Asio 1.32.0 加载成功！" << std::endl;
    return 0;
}