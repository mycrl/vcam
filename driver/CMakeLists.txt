cmake_minimum_required(VERSION 3.5)
project(vcam-driver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

add_library(vcam-driver SHARED
            vcam.cpp
            ../service/shared_memory_queue.cpp
            ../service/nv12_scale.cpp)

include_directories("../service")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_property(TARGET vcam-driver PROPERTY MSVC_RUNTIME_LIBRARY MultiThreaded)
else()
    set_property(TARGET vcam-driver PROPERTY MSVC_RUNTIME_LIBRARY MultiThreadedDebug)
endif()