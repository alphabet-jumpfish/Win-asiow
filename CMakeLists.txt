cmake_minimum_required(VERSION 3.21)
project(asiow)

set(CMAKE_CXX_STANDARD 20)

# 定义 Windows 版本 (Windows 7 及以上)
if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()

# 1. 查找 Asio
find_package(PkgConfig REQUIRED)
pkg_check_modules(ASIO REQUIRED asio)

# 2. 将 main.cpp 声明为 asiow 项目的入口
add_executable(asiow main.cpp)

# 3. 链接 Asio 和 Windows 库
target_include_directories(asiow PRIVATE ${ASIO_INCLUDE_DIRS})
target_link_libraries(asiow PRIVATE ${ASIO_LIBRARIES})

if(WIN32)
    target_link_libraries(asiow PRIVATE ws2_32 wsock32)
endif()

