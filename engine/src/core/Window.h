#pragma once

#include <memory>
#include <queue>
#include <variant>

namespace BitCrush {
    namespace Events {
        // C++ Magic to make it work
        template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
        template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

        struct EWindowClose {};
        struct EInput {};

        using Event = std::variant<EWindowClose, EInput>;

    }

    class Window {
    public:
        Window();
        ~Window();

        void Update();
        void Open();
        void PushEvent(Events::Event event);

        struct WImplementation;
        std::unique_ptr<WImplementation> impl;


    private:
        void PoolEvents();
        void CloseWindow();

        std::queue<Events::Event> event_queue;
    };
}
