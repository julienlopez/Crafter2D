#-------------------------------------------------
#
# Project created by QtCreator 2011-09-25T12:08:01
#
#-------------------------------------------------

QT       += core gui network

TARGET = Crafter2Dclient
TEMPLATE = app

INCLUDEPATH += "../include"
LIBS += -L../Crafter2Dlib-build-desktop-Qt_4_7_3_for_Desktop_-_MinGW_4_4__Qt_SDK__Debug/debug
LIBS += -lCrafter2Dlib

SOURCES += main.cpp\
        mainwindow.cpp \
    loginwidget.cpp

HEADERS  += mainwindow.hpp \
    loginwidget.hpp


