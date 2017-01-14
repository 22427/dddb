
QT       += core

QT       -= gui

TARGET = dddb 
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
   main.cpp \
    DDDB.cpp

CONFIG += c++11

INCLUDEPATH += ./
LIBS += 


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
    VertexData.h

