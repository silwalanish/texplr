#pragma once

#include <cstdint>
#include <eventpp/eventdispatcher.h>
#include <functional>
#include <string>

namespace texplr {

struct WindowSpecification {
    uint16_t width;
    uint16_t height;
    std::string title;

    bool isResizable = false;
};

enum WindowEvents {
    WINDOW_CLOSE,
};

class GameWindow : public eventpp::EventDispatcher<WindowEvents, void(const GameWindow&)> {
public:
    GameWindow(const WindowSpecification& specs);
    ~GameWindow();

    void init();
    void destroy();

    void* getNativeHandle() const;

    const WindowSpecification& getSpecs() const;

private:
    WindowSpecification m_specs;
    void* m_handle = nullptr;
};

} // namespace texplr
