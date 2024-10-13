#include <texplr/core/surface/glfw_context.h>

#include <stdexcept>
#include <string>

#include <GLFW/glfw3.h>

namespace texplr {

GLFWContext::GLFWContext(const GLFWSpecification& specs)
    : m_isInitialized(false)
    , m_specs(specs)
{
}

GLFWContext::~GLFWContext()
{
    destroy();
}

void GLFWContext::init()
{
    if (m_isInitialized) {
        return;
    }

    if (!glfwInit()) {
        throw std::runtime_error("Couldn't initialize GLFW!");
    }

    glfwSetErrorCallback([](int error, const char* description) {
        throw std::runtime_error(std::string(description));
    });

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    m_isInitialized = true;
}

void GLFWContext::pollEvents()
{
    glfwPollEvents();
}

void GLFWContext::destroy()
{
    if (m_isInitialized) {
        glfwTerminate();

        m_isInitialized = false;
    }
}

const GLFWSpecification& GLFWContext::getSpecs() const
{
    return m_specs;
}

} // namespace texplr
