#include "HelloController.h"
#include "../service/HelloService.h"

HelloController::HelloController()
    : service_(std::make_unique<HelloService>()) {
}

HelloController::~HelloController() = default;

std::string HelloController::handleHello(const std::string& name) {
    return service_->sayHello(name);
}
