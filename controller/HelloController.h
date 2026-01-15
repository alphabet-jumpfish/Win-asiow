/**
 * @file HelloController.h
 * @brief Hello 控制器头文件
 *
 * 该文件定义了 HelloController 类，负责处理客户端的 Hello 请求。
 * 控制器层作为 MVC 架构中的 Controller，接收请求并调用服务层处理业务逻辑。
 */

#ifndef HELLOCONTROLLER_H
#define HELLOCONTROLLER_H

#include <string>
#include <memory>

// 前向声明 HelloService 类，避免头文件循环依赖
class HelloService;

/**
 * @class HelloController
 * @brief Hello 请求控制器
 *
 * 该类负责处理与 Hello 相关的请求，遵循单一职责原则。
 * 使用依赖注入模式，通过 unique_ptr 持有 HelloService 实例。
 */
class HelloController {
public:
    /**
     * @brief 构造函数
     *
     * 初始化控制器，创建 HelloService 实例。
     * 使用 std::make_unique 确保异常安全。
     */
    HelloController();

    /**
     * @brief 析构函数
     *
     * 使用默认析构函数，unique_ptr 会自动释放 HelloService 资源。
     */
    ~HelloController();

    /**
     * @brief 处理 Hello 请求
     *
     * 接收客户端发送的名字，调用服务层生成问候消息。
     *
     * @param name 客户端发送的名字（const 引用避免拷贝）
     * @return std::string 返回格式化的问候消息
     *
     * @note 该方法是线程安全的，可以被多个线程同时调用
     *
     * @example
     * HelloController controller;
     * std::string response = controller.handleHello("Alice");
     * // response: "Hello, Alice! Welcome to ASIO Server."
     */
    std::string handleHello(const std::string& name);

private:
    /**
     * @brief 服务层实例
     *
     * 使用 unique_ptr 管理 HelloService 生命周期，确保：
     * 1. 自动内存管理，防止内存泄漏
     * 2. 独占所有权，符合控制器-服务的一对一关系
     * 3. 支持前向声明，减少编译依赖
     */
    std::unique_ptr<HelloService> service_;
};

#endif // HELLOCONTROLLER_H
