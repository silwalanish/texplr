#pragma once

#include <string>

namespace texplr {

struct VulkanSpecification {
    std::string appName;
    std::string engineName;
};

class VulkanContext {
public:
    VulkanContext(const VulkanSpecification& specs);
    ~VulkanContext();

    void init();
    void destroy();

    const VulkanSpecification& getSpecs() const;

private:
    VulkanSpecification m_specs;
    void* m_instance;
};

} // namespace texplr
