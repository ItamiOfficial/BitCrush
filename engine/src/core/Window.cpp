#include "Window.h"

#include <print>

namespace BitCrush {
    void Window::Update() {
        using namespace Events;

        PoolEvents();

        while (!event_queue.empty()) {
            auto event = event_queue.front();
            event_queue.pop();

            std::visit(overloaded {
                [this] (EWindowClose &) {
                    std::print("Close Window");
                    CloseWindow();
                },
                [this] (EInput &) { ; },
            }, event);
        }
    }
}
