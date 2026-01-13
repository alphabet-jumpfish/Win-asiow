#ifndef HELLOCONTROLLER_H
#define HELLOCONTROLLER_H

#include <string>
#include <memory>

// 前向声明
class HelloService;

class HelloController {
public:
    HelloController();
    ~HelloController();

    // 处理 /hello 请求
    std::string handleHello(const std::string& name);

private:
    std::unique_ptr<HelloService> service_;
};

#endif // HELLOCONTROLLER_H
