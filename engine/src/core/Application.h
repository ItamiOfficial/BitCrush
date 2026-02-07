#pragma once
#include <memory>
#include <vector>

#include "Window.h"

namespace BitCrush {
    class Application {

    public:
        void Init();
        bool exitProgram {false};
        static Application& Get() {
            static Application instance {};
            return instance;
        }

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

    private:
        std::vector<std::unique_ptr<Window>> windows {};
        void CreateWindow();
        void Run();
        void Exit();


        Application() = default;
    };
}
