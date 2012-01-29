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
        mainwindow.cpp \
    loginwidget.cpp \
    screenwidget.cpp \
    debugdock.cpp \
    scene.cpp \
    store.cpp \
    cplayer.cpp \
    cworldelement.cpp \
    terrainmanager.cpp \
    inventorydock.cpp

HEADERS  += mainwindow.hpp \
    loginwidget.hpp \
    screenwidget.hpp \
    debugdock.hpp \
    scene.hpp \
    store.hpp \
    cplayer.hpp \
    cworldelement.hpp \
    terrainmanager.hpp \
    inventorydock.hpp












