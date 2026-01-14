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

# 安装目标可执行文件
install(TARGETS server_main client_main
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

# Windows 平台：安装运行时依赖的 DLL
if (WIN32)
    # 安装 MinGW 运行时 DLL（如果使用 MinGW）
    if (MINGW)
        get_filename_component(MINGW_BIN_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)
        install(FILES
                "${MINGW_BIN_DIR}/libgcc_s_seh-1.dll"
                "${MINGW_BIN_DIR}/libstdc++-6.dll"
                "${MINGW_BIN_DIR}/libwinpthread-1.dll"
                DESTINATION bin
                OPTIONAL
        )
    endif()
endif()

# CPack 打包配置
set(CPACK_PACKAGE_NAME "asiow")
set(CPACK_PACKAGE_VENDOR "Wangjiawen")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ASIO Server and Client Application")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

# 设置打包格式
if (WIN32)
    # Windows 推荐使用 ZIP 格式
    set(CPACK_GENERATOR "ZIP")
    # 如果需要生成安装包，可以使用 NSIS
    # set(CPACK_GENERATOR "NSIS")
    # 或者同时生成两种格式
    # set(CPACK_GENERATOR "ZIP;NSIS")
else()
    set(CPACK_GENERATOR "TGZ")
endif()

include(CPack)
