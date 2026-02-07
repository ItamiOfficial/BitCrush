#include "core/Window.h"
#include <Cocoa/Cocoa.h>

struct BitCrush::Window::WImplementation {
    NSWindow* nswindow;
};

namespace BitCrush {
    Window::Window() : impl(std::make_unique<WImplementation>()) {}
    Window::~Window() { CloseWindow(); }

    void Window::Open() {
        NSRect frame = NSMakeRect(0, 0, 1280, 720);
        impl->nswindow = [[NSWindow alloc] initWithContentRect:frame
                                                    styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable)
                                                      backing:NSBackingStoreBuffered
                                                        defer:NO];

        [impl->nswindow setTitle:@"BitCrush Engine (Mac)"];
        [impl->nswindow makeKeyAndOrderFront:nil];
    }

    void Window::PoolEvents() {
        NSEvent* event = nil;

        do {
            event = [NSApp nextEventMatchingMask:NSEventMaskAny
                untilDate:[NSDate distantPast]
                inMode:NSDefaultRunLoopMode
                dequeue:YES];

            if (event) {
                [NSApp sendEvent:event];
            }
        } while (event != nil);
    }

    void Window::CloseWindow() {
        if (impl->nswindow) {
            [impl->nswindow close];
            impl->nswindow = nil;
        }
    }
}
