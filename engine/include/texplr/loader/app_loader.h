#pragma once

#include <texplr/core/application.h>

namespace texplr {

class AppLoader {
public:
    static ApplicationSpecification loadSpecs(const std::string& path);
};

} // namespace texplr
