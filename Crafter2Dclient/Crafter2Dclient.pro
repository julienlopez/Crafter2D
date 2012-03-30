#-------------------------------------------------
#
# Project created by QtCreator 2011-09-25T12:08:01
#
#-------------------------------------------------

QT       += core gui network

TARGET = Crafter2Dclient
TEMPLATE = app

INCLUDEPATH += "../include"
LIBS += -L../Crafter2Dlib/debug
LIBS += -lCrafter2Dlib

SOURCES += main.cpp\
        ui/mainwindow.cpp \
    ui/loginwidget.cpp \
    ui/screenwidget.cpp \
    ui/debugdock.cpp \
    scene.cpp \
    store.cpp \
    cplayer.cpp \
    cworldelement.cpp \
    terrainmanager.cpp \
    ui/inventorydock.cpp \
    ui/menu/menu.cpp \
    ui/menu/textentry.cpp \
    cmiscellaneous.cpp \
    cstaticobject.cpp

HEADERS  += ui/mainwindow.hpp \
    ui/loginwidget.hpp \
    ui/screenwidget.hpp \
    ui/debugdock.hpp \
    scene.hpp \
    store.hpp \
    cplayer.hpp \
    cworldelement.hpp \
    terrainmanager.hpp \
    ui/inventorydock.hpp \
    ui/menu/menu.hpp \
    ui/menu/textentry.hpp \
    cmiscellaneous.hpp \
    cstaticobject.hpp












