cmake_minimum_required(VERSION 4.1)
project(BitCrush VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(BitCrush STATIC)
target_include_directories(BitCrush PUBLIC engine/src)

target_sources(BitCrush
    PUBLIC
        engine/src/utility/Types.h
        engine/src/core/Application.cpp
        engine/src/core/Application.h
        engine/src/core/Window.cpp
        engine/src/core/Window.h
)

# Platform Specific implementations
if(WIN32)
    target_sources(BitCrush PUBLIC engine/src/platforms/windows/Window_Win32.cpp)
elseif(APPLE)
    target_sources(BitCrush PUBLIC
        engine/src/platforms/macos/Window_MacOS.mm
        engine/src/platforms/macos/Application_MacOS.mm
    )
    target_link_libraries(BitCrush PRIVATE "-framework Cocoa")
endif()

add_executable(BitCrush_App main.cpp)

target_link_libraries(BitCrush_App PRIVATE BitCrush)