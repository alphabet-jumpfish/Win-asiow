#ifndef HELLOSERVICE_H
#define HELLOSERVICE_H

#include <string>

class HelloService {
public:
    HelloService();
    ~HelloService();

    // 业务逻辑：生成问候语
    std::string sayHello(const std::string& name);
};

#endif // HELLOSERVICE_H
