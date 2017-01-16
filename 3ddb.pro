
QT       += core

QT       -= gui

TARGET = dddb 
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += link_pkgconfig

PKGCONFIG += glfw3

TEMPLATE = app

SOURCES += \
   main.cpp \
    DDDB.cpp \
    DDDB_operations.cpp \
    deps/glad/src/glad.c

CONFIG += c++11

INCLUDEPATH += ./ ./deps/glad/include
LIBS = -lGL -lGLU -lX11 -lXxf86vm -lXrandr -pthread -lXi -ldl

DESTDIR = bin
OBJECTS_DIR = obj

HEADERS += \
    Animation.h \
    Cmap.h \
    DDDB.h \
    Material.h \
    Mesh.h \
    Object.h \
    Shadow.h \
    util.h \
    VertexData.h \
    DDDB_operations.h

