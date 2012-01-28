#-------------------------------------------------
#
# Project created by QtCreator 2011-11-03T07:20:23
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = Crafter2Dcommand
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += "../include"
LIBS += -L../Crafter2Dlib/debug
LIBS += -lCrafter2Dlib

SOURCES += main.cpp \
    cmd.cpp

HEADERS += \
    cmd.hpp


