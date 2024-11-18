cmake_minimum_required(VERSION 3.25)
project(framework)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(framework
        CommonTypes.h
        fw_config.h
        glerror.cpp
        glerror.h
        Input.cpp
        Input.h
        libheaders.h
        OBJLoader.cpp
        OBJLoader.h
        OpenGLWindow.cpp
        OpenGLWindow.h)
