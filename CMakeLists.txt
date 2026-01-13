cmake_minimum_required(VERSION 3.21)
project(asiow)

set(CMAKE_CXX_STANDARD 20)

# 1. 增强宏定义
if(WIN32)
    # 将版本提升到 Win10 以支持更多特性，并定义独立版宏
    add_definitions(-D_WIN32_WINNT=0x0A00 -DASIO_STANDALONE)
endif()

# 1. 查找 Asio
find_package(PkgConfig REQUIRED)
pkg_check_modules(ASIO REQUIRED asio)

# 2. 将 main.cpp 声明为 asiow 项目的入口
add_executable(asiow
        main.cpp
        controller/HelloController.cpp
        controller/HelloController.h
        service/HelloService.cpp
        service/HelloService.h
)

# 3. 链接 Asio 和 Windows 库
target_include_directories(asiow PRIVATE ${ASIO_INCLUDE_DIRS})
target_link_libraries(asiow PRIVATE ${ASIO_LIBRARIES})

# 2. 链接更完整的网络库
if(WIN32)
    # 增加 mswsock，这是 Asio 处理高级 Socket 操作常需要的
    target_link_libraries(asiow PRIVATE ws2_32 wsock32 mswsock)
endif()
