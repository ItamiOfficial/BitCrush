#include <windows.h>
#include "core/Window.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

struct BitCrush::Window::WImplementation {
    HWND handle {};
    HINSTANCE  instance {};
};

namespace BitCrush {

    Window::Window() : impl(std::make_unique<WImplementation>()) {}

    Window::~Window() {
        CloseWindow();
    }

    void Window::Open() {
        const wchar_t ClassName[] = L"BitCrushWindowClass";
        impl->instance = GetModuleHandle(nullptr);

        WNDCLASSEXW wc = {};
        wc.cbSize = sizeof(WNDCLASSEXW);
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = impl->instance;
        wc.lpszClassName = ClassName;
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

        RegisterClassExW(&wc);

        impl->handle = CreateWindowExW(
            0, ClassName, L"BitCrush Engine",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
            nullptr, nullptr, wc.hInstance,
            this // Übergabe des C++ Objekts an Win32
        );

        if (impl->handle) {
            ShowWindow(impl->handle, SW_SHOWDEFAULT);
        }
    }

    void Window::PoolEvents() {
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    void Window::PushEvent(Events::Event event) {
        event_queue.push(event);
    }

    void Window::CloseWindow() {
        if (impl && impl->handle) {
            ::DestroyWindow(impl->handle);
            impl->handle = nullptr;
        }
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    BitCrush::Window* pWindow = nullptr;

    if (uMsg == WM_NCCREATE) {
        auto* pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
        pWindow = static_cast<BitCrush::Window *>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
    } else {
        pWindow = reinterpret_cast<BitCrush::Window *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    using namespace BitCrush::Events;

    if (pWindow) {
        switch (uMsg) {
            case WM_CLOSE:
                pWindow->PushEvent(EWindowClose{});
                return 0;
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
        }
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

/*
void BitCrush::Window::Open() {
    const wchar_t ClassName[] = L"BitCrush Engine";

    // Create Class
    WNDCLASSEXW wc = { };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = ClassName;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    RegisterClassExW(&wc);

    impl->hwnd = CreateWindowExW(
        0,                          // Optional Window Styles
        ClassName,                  // Class
        L"BitCrush Engine Window",  // Window Text
        WS_OVERLAPPEDWINDOW,        // Window Style
        CW_USEDEFAULT,              // Position
        CW_USEDEFAULT,              // Position
        1280,                       // Size
        720,                        // Size
        nullptr,                    // Parent Window
        nullptr,                    // Menu
        wc.hInstance,               // Instance Handle
        this                        // Pointer to Window.h class
        );

    if (hwnd == nullptr) {
        return;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
}

void BitCrush::Window::PoolEvents() {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void BitCrush::Window::DestroyWindow() {
    DestroyWindow(impl->);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {

        }
        case WM_DESTROY:
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

*/