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
    commande/commande.cpp \
    commande/status.cpp \
    commande/shutdown.cpp \
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
    message/screen/sendposition.cpp \
    gplayer.cpp \
    gbuilding.cpp \
    gobject.cpp \
    gstaticobject.cpp \
    position.cpp \
    utils.cpp \
    worldelement.cpp \
    commande/statusupdate.cpp \
    idset.cpp \
    message/screen/objectinformation.cpp \
    message/screen/majposition.cpp \
    message/screen/requestobjectinformation.cpp

HEADERS +=\
    commande/commande.hpp \
    commande/status.hpp \
    commande/shutdown.hpp \
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
    message/screen/sendposition.hpp \
    gplayer.hpp \
    gobject.hpp \
    gbuilding.hpp \
    gstaticobject.hpp \
    position.hpp \
    utils.hpp \
    worldelement.hpp \
    commande/statusupdate.hpp \
    idset.hpp \
    message/screen/objectinformation.hpp \
    message/screen/majposition.hpp \
    message/screen/requestobjectinformation.hpp











































