cmake_minimum_required(VERSION 3.10)
project(Live2dWidget)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_BUILD_TYPE Debug)

find_package(Qt5 COMPONENTS Core Gui OpenGL X11Extras REQUIRED)

include_directories(
        Core/include
        CubismNativeFramework/src
        thirdParty/stb
)

link_directories(.)

set(PROJECT_HEADERS
        CubismNativeFramework/src/Rendering/CubismRenderer.hpp
        CubismNativeFramework/src/Rendering/OpenGL/CubismOffscreenSurface_OpenGLES2.hpp
        CubismNativeFramework/src/Rendering/OpenGL/CubismRenderer_OpenGLES2.hpp
        CubismNativeFramework/src/Rendering/OpenGL/openglhelper.hpp
        QtLive2d/LAppAllocator.hpp
        QtLive2d/LAppDefine.hpp
        QtLive2d/LAppDelegate.hpp
        QtLive2d/LAppLive2DManager.hpp
        QtLive2d/LAppModel.hpp
        QtLive2d/LAppPal.hpp
        QtLive2d/LAppSprite.hpp
        QtLive2d/LAppTextureManager.hpp
        QtLive2d/LAppView.hpp
        QtLive2d/LAppWavFileHandler.hpp
        QtLive2d/QLive2dWidget.hpp
        QtLive2d/TouchManager.hpp
        QtLive2d/openglhelper.hpp
)
set(PROJECT_SOURCES
        CubismNativeFramework/src/Rendering/CubismRenderer.cpp
        CubismNativeFramework/src/Rendering/OpenGL/CubismOffscreenSurface_OpenGLES2.cpp
        CubismNativeFramework/src/Rendering/OpenGL/CubismRenderer_OpenGLES2.cpp
        QtLive2d/LAppAllocator.cpp
        QtLive2d/LAppDefine.cpp
        QtLive2d/LAppDelegate.cpp
        QtLive2d/LAppLive2DManager.cpp
        QtLive2d/LAppModel.cpp
        QtLive2d/LAppPal.cpp
        QtLive2d/LAppSprite.cpp
        QtLive2d/LAppTextureManager.cpp
        QtLive2d/LAppView.cpp
        QtLive2d/LAppWavFileHandler.cpp
        QtLive2d/QLive2dWidget.cpp
        QtLive2d/TouchManager.cpp
)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_executable(MainWindow ${PROJECT_SOURCES} test/main.cpp test/MainWindow.cpp test/mouseEventThread.cpp test/MainWindow.h test/mouseEventThread.h)
    target_link_libraries(MainWindow
            Qt5::Core
            Qt5::Gui
            Qt5::X11Extras
            Qt5::OpenGL
            -lX11
            -lXext
            -lXtst
            -lLive2dWidget
            -lGL
            -lFramework
            -lLive2DCubismCore
            -L.
    )
endif ()

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::X11Extras
        Qt5::OpenGL
        -lX11
        -lXext
        -lLive2dWidget
        -lGL
        -lFramework
        -lLive2DCubismCore
        -L.
)