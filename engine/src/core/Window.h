#pragma once
#include <memory>

namespace BitCrush {

    /*
     * Window is class which names a struct which differs in implementation depending on the system.
     * Each System has its own file, and when compiled only the relevant file will get loaded.
     * These files also implement the Functions of Window.
     * Constructor and Destructor must be delcared here, and defined in their respective platform files
     */
    class Window
    {
    public:
        // ==== Section: Platform implementation specific code ==== //
        Window();
        ~Window();
        void Open();
        void Close();
        bool IsOpen();
        void ProcessEvents();

        // ==== Section: API ==== //
        void Run() {
            Open();
            while (IsOpen()) {
                ProcessEvents();
            }
        }

    private:
        struct Implementation;
        std::unique_ptr<Implementation> implementation;
    };
}
