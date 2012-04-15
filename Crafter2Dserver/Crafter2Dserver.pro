#-------------------------------------------------
#
# Project created by QtCreator 2011-09-25T11:18:08
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += sql
QT       -= gui

TARGET = Crafter2Dserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += "../include"
LIBS += -L../Crafter2Dlib/debug
LIBS += -lCrafter2Dlib

SOURCES += main.cpp \
    serveur.cpp \
    client.cpp \
    messagehandler.cpp \
    screenmessagehandler.cpp \
    clientinfo.cpp \
    dataaccessor.cpp \
    playeraccessor.cpp \
    buildingaccessor.cpp \
    objectaccessor.cpp \
    staticobjectaccessor.cpp \
    splayer.cpp \
    sutils.cpp \
    sbuilding.cpp \
    sobject.cpp \
    sstaticobject.cpp \
    localserveur.cpp \
    stree.cpp

HEADERS += \
    serveur.hpp \
    client.hpp \
    messagehandler.hpp \
    screenmessagehandler.hpp \
    clientinfo.hpp \
    dataaccessor.hpp \
    faccessor.hpp \
    playeraccessor.hpp \
    buildingaccessor.hpp \
    objectaccessor.hpp \
    staticobjectaccessor.hpp \
    splayer.hpp \
    sutils.hpp \
    sworldelement.hpp \
    sbuilding.hpp \
    sobject.hpp \
    sstaticobject.hpp \
    localserveur.hpp \
    stree.hpp






































