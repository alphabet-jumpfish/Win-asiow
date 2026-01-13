cmake_minimum_required(VERSION 3.21)
project(asiow)

set(CMAKE_CXX_STANDARD 20)

# 1. 查找 Asio
find_package(PkgConfig REQUIRED)
pkg_check_modules(ASIO REQUIRED asio)

# 2. 将 main.cpp 声明为 asiow 项目的入口
add_executable(asiow main.cpp)

# 3. 注入头文件、宏定义和网络库
target_include_directories(asiow PRIVATE ${ASIO_INCLUDE_DIRS})
target_compile_definitions(asiow PRIVATE ASIO_STANDALONE _WIN32_WINNT=0x0A00)
target_link_libraries(asiow PRIVATE ${ASIO_LIBRARIES} ws2_32 mswsock)