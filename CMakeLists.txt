cmake_minimum_required(VERSION 3.21)
project(server_main)

set(CMAKE_CXX_STANDARD 20)

# 增强宏定义
if (WIN32)
    # 将版本提升到 Win10 以支持更多特性，并定义独立版宏
    add_definitions(-D_WIN32_WINNT=0x0A00 -DASIO_STANDALONE)
endif ()

# 查找 Asio
find_package(PkgConfig REQUIRED)
pkg_check_modules(ASIO REQUIRED asio)

# 通用函数：为目标链接 ASIO 和网络库
function(link_asio_libraries target_name)
    target_include_directories(${target_name} PRIVATE ${ASIO_INCLUDE_DIRS})
    target_link_libraries(${target_name} PRIVATE ${ASIO_LIBRARIES})

    if (WIN32)
        target_link_libraries(${target_name} PRIVATE ws2_32 wsock32 mswsock)
    endif ()
endfunction()

# 服务器可执行文件
add_executable(server_main
        ServerMain.cpp
        Server.cpp
        Server.h
        controller/HelloController.cpp
        controller/HelloController.h
        service/HelloService.cpp
        service/HelloService.h
)
link_asio_libraries(server_main)

# 客户端可执行文件
add_executable(client_main
        ClientMain.cpp
        Client.cpp
        Client.h
)
link_asio_libraries(client_main)
