/**
 * @file HelloController.cpp
 * @brief Hello 控制器实现文件
 *
 * 该文件实现了 HelloController 类的所有方法。
 * 控制器负责协调请求处理流程，将具体业务逻辑委托给服务层。
 */

#include "HelloController.h"
#include "../service/HelloService.h"

/**
 * @brief HelloController 构造函数实现
 *
 * 使用成员初始化列表创建 HelloService 实例。
 * std::make_unique 的优势：
 * 1. 异常安全：如果构造函数抛出异常，不会造成内存泄漏
 * 2. 性能优化：只进行一次内存分配
 * 3. 代码简洁：避免显式 new 操作
 */
HelloController::HelloController()
    : service_(std::make_unique<HelloService>()) {
}

/**
 * @brief HelloController 析构函数实现
 *
 * 使用 = default 让编译器生成默认析构函数。
 * unique_ptr 会自动调用 HelloService 的析构函数，无需手动释放资源。
 *
 * 注意：
 * - 析构函数必须在 .cpp 文件中定义（即使是 = default）
 * - 因为使用了前向声明，如果在头文件中定义会导致编译错误
 * - unique_ptr 的析构需要完整的类型定义
 */
HelloController::~HelloController() = default;

/**
 * @brief 处理 Hello 请求的实现
 *
 * 该方法是控制器的核心业务处理方法，遵循以下设计原则：
 * 1. 单一职责：只负责请求转发，不包含业务逻辑
 * 2. 依赖倒置：依赖 HelloService 抽象，而非具体实现
 * 3. 开闭原则：对扩展开放，对修改关闭
 *
 * @param name 客户端传入的名字参数
 *             使用 const std::string& 避免不必要的拷贝，提高性能
 *
 * @return std::string 返回服务层生成的问候消息
 *                     返回值优化（RVO）会避免额外的拷贝开销
 *
 * 调用流程：
 * Client -> Server -> HelloController::handleHello() -> HelloService::sayHello()
 *
 * 语法说明：
 * - service_->sayHello(name)：使用箭头操作符调用 unique_ptr 指向对象的方法
 * - 等价于 (*service_).sayHello(name)
 * - unique_ptr 重载了 operator-> 和 operator*，使其行为类似原始指针
 */
std::string HelloController::handleHello(const std::string& name) {
    return service_->sayHello(name);
}
