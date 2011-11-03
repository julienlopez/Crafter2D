#-------------------------------------------------
#
# Project created by QtCreator 2011-09-25T11:14:59
#
#-------------------------------------------------

QT       += network

TARGET = Crafter2Dlib
TEMPLATE = lib

DEFINES += CRAFTER2DLIB_LIBRARY

INCLUDEPATH += ../include

SOURCES += \
    utils.cpp \
    position.cpp \
    message/message.cpp \
    message/login.cpp \
    message/loginfailure.cpp \
    message/loginsuccess.cpp \
    message/erreur/erreur.cpp \
    message/erreur/erreurserveur.cpp \
    message/erreur/erreurclient.cpp \
    message/screen/getposition.cpp \
    message/screen/screen.cpp \
    message/screen/setposition.cpp \
    worldelement.cpp \
    gplayer.cpp \
    gbuilding.cpp \
    gobject.cpp \
    gstaticobject.cpp \
    message/screen/sendposition.cpp \
    commande/commande.cpp \
    commande/status.cpp \
    shutdown.cpp

HEADERS +=\
    utils.hpp \
    position.hpp \
    message/message.hpp \
    message/login.hpp \
    message/loginfailure.hpp \
    message/loginsuccess.hpp \
    message/erreur/erreur.hpp \
    message/erreur/erreurserveur.hpp \
    message/erreur/erreurclient.hpp \
    message/screen/getposition.hpp \
    message/screen/screen.hpp \
    message/screen/setposition.hpp \
    worldelement.hpp \
    gplayer.hpp \
    gobject.hpp \
    gbuilding.hpp \
    gstaticobject.hpp \
    message/screen/sendposition.hpp \
    commande/commande.hpp \
    commande/status.hpp \
    shutdown.hpp






































