cmake_minimum_required(VERSION 4.1)
project(BitCrush VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Maybe makes it work
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_library(BitCrush STATIC)

target_sources(BitCrush
    PUBLIC
        engine/src/core/Window.h
        engine/src/core/Types.h
)

if(WIN32)
    target_sources(BitCrush
        PUBLIC
            engine/src/platforms/windows/Window_Win32.cpp
    )

endif()

add_executable(BitCrush_App main.cpp)

target_link_libraries(BitCrush_App PRIVATE BitCrush)