#-------------------------------------------------
#
# Project created by QtCreator 2011-09-25T11:18:08
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = Crafter2Dserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += "../include"
LIBS += -L../Crafter2Dlib-build-desktop-Qt_4_7_3_for_Desktop_-_MinGW_4_4__Qt_SDK__Debug/debug
LIBS += -lCrafter2Dlib

SOURCES += main.cpp \
    serveur.cpp \
    client.cpp

HEADERS += \
    serveur.hpp \
    client.hpp




