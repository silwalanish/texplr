#pragma once

namespace texplr {

struct GLFWSpecification {
};

class GLFWContext {
public:
    GLFWContext(const GLFWSpecification& specs);
    ~GLFWContext();

    void init();
    void pollEvents();
    void destroy();

    const GLFWSpecification& getSpecs() const;

private:
    bool m_isInitialized;
    GLFWSpecification m_specs;
};

} // namespace texplr
