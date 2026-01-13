#include "HelloService.h"

HelloService::HelloService() = default;

HelloService::~HelloService() = default;

std::string HelloService::sayHello(const std::string& name) {
    if (name.empty()) {
        return "Hello, World!";
    }
    return "Hello, " + name + "!";
}
