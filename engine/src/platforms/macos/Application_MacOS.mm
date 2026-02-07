#include <Cocoa/Cocoa.h>
#include "core/Application.h"

namespace BitCrush {
    void Application::PlatformInitialize() {
        [NSApplication sharedApplication];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        [NSApp activateIgnoringOtherApps:YES];
        [NSApp finishLaunching];
    }
}