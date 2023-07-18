QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets
CONFIG += c++17
TARGET = Live2dWidget

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/Core/include
INCLUDEPATH += $$PWD/CubismNativeFramework/src
INCLUDEPATH += $$PWD/thirdParty/stb
DEPENDPATH += $$PWD/../dll


# DEFINES += WIN32
# DEFINES += _WINDOWS
# DEFINES += CSM_TARGET_WIN_GL

CONFIG += debug_and_release

CONFIG(debug, debug|release){
    message(Debug build)
    LIBS += -lLive2DCubismCore
    LIBS += -lFramework
    LIBS += -lX11 -lXext -lXi
    QT += x11extras
    SOURCES += Sample/main.cpp\
            Sample/mainwindow.cpp
    HEADERS += Sample/mainwindow.h
    FORMS += Sample/mainwindow.ui

}

CONFIG(release, debug|release){
    message(Release build)
    TEMPLATE = lib
    LIBS += -lLive2DCubismCore
    LIBS += -lFramework
    LIBS += -L$$PWD/lib
    CONFIG += staticlib
}

LIBS += -lGL

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    CubismNativeFramework/src/Rendering/CubismRenderer.hpp \
    CubismNativeFramework/src/Rendering/OpenGL/CubismOffscreenSurface_OpenGLES2.hpp \
    CubismNativeFramework/src/Rendering/OpenGL/CubismRenderer_OpenGLES2.hpp \
    CubismNativeFramework/src/Rendering/OpenGL/openglhelper.hpp \
    QtLive2d/LAppAllocator.hpp \
    QtLive2d/LAppDefine.hpp \
    QtLive2d/LAppDelegate.hpp \
    QtLive2d/LAppLive2DManager.hpp \
    QtLive2d/LAppModel.hpp \
    QtLive2d/LAppPal.hpp \
    QtLive2d/LAppSprite.hpp \
    QtLive2d/LAppTextureManager.hpp \
    QtLive2d/LAppView.hpp \
    QtLive2d/LAppWavFileHandler.hpp \
    QtLive2d/QLive2dWidget.hpp \
    QtLive2d/TouchManager.hpp \
    QtLive2d/openglhelper.hpp \
#    Sample/mainwindow.h

SOURCES += \
    CubismNativeFramework/src/Rendering/CubismRenderer.cpp \
    CubismNativeFramework/src/Rendering/OpenGL/CubismOffscreenSurface_OpenGLES2.cpp \
    CubismNativeFramework/src/Rendering/OpenGL/CubismRenderer_OpenGLES2.cpp \
    QtLive2d/LAppAllocator.cpp \
    QtLive2d/LAppDefine.cpp \
    QtLive2d/LAppDelegate.cpp \
    QtLive2d/LAppLive2DManager.cpp \
    QtLive2d/LAppModel.cpp \
    QtLive2d/LAppPal.cpp \
    QtLive2d/LAppSprite.cpp \
    QtLive2d/LAppTextureManager.cpp \
    QtLive2d/LAppView.cpp \
    QtLive2d/LAppWavFileHandler.cpp \
    QtLive2d/QLive2dWidget.cpp \
    QtLive2d/TouchManager.cpp \
#    Sample/main.cpp \
#   Sample/mainwindow.cpp

#FORMS += \
#    Sample/mainwindow.ui

