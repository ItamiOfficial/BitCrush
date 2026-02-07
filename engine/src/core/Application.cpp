#include "Application.h"
#include <print>

namespace BitCrush {
    /*
     * Init setup's all the different Components of the Engine
     * 1 -> Inits Asset Manager
     * 2 -> Creates a Window
     * 2.1 -> Setup's EventQueue
     * 2.2 -> Activates Input System
     * 2.3 -> Creates a Vulkan/MoltenVK rendering Setup
     * 2.4 -> Creates Sound Backend
     * 3 -> Load's WorldData and starts Program
     * 4 -> Run Application
     */
    void Application::Init() {
        // 2. Create Window
        CreateWindow();

        // 4. Start Application Runtime
        Run();
    }

    void Application::CreateWindow() {
        auto window = std::make_unique<Window>();
        window->Open();
        windows.push_back(std::move(window));
    }

    void Application::Run() {
        while (!windows.empty() && !exitProgram) {
            for (auto& window : windows) {
                window->Update();
            }
        }

        Exit();
    }

    void Application::Exit() {

    }
}
