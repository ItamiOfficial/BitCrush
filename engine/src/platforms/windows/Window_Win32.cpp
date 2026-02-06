#include <windows.h>
#include "../../core/Window.h"

// == Section: Win32 Implementation of Window == //
struct BitCrush::Window::Implementation
{
    HWND handle {};
    HINSTANCE instance {};
    const wchar_t* className = L"BitCrushEngine Window";
    bool isRunning = true;
};

// == Section: Destruct/Constructor == //
BitCrush::Window::Window() : implementation(std::make_unique<Implementation>()) {}
BitCrush::Window::~Window() = default;

bool BitCrush::Window::IsOpen() {
    return implementation->isRunning;
}

// == Section: Event Queue == //
void BitCrush::Window::ProcessEvents()
{
    MSG mgs = {};
    while (PeekMessage(&mgs, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&mgs);
        DispatchMessage(&mgs);
    }
}

// == Section: ??? == //
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    BitCrush::Window* window = nullptr;

    // Gets Triggered when window is created.
    if (msg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        window = (BitCrush::Window*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
    }
    else {
        window = (BitCrush::Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    // If Window is hopefully created
    if (window) {
        if (msg == WM_CLOSE) {
            window->Close();
            return 0;
        }

        if (msg == WM_DESTROY) {
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// == Section: Create Window == //

void BitCrush::Window::Open()
{
    implementation->instance = GetModuleHandle(nullptr);

    // Create Window Class
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = implementation->instance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = implementation->className;

    RegisterClassExW(&wc);

    // Create Window
    implementation->handle = CreateWindowExW(
        0,
        implementation->className,
        L"BitCrush Engine",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
        nullptr, nullptr, implementation->instance, this
    );

    if (implementation->handle) {
        ShowWindow(implementation->handle, SW_SHOW);
    }
}

void BitCrush::Window::Close() {
    if (implementation->handle) {
        DestroyWindow(implementation->handle);
        implementation->handle = nullptr;
    }

    implementation->isRunning = false;
}
