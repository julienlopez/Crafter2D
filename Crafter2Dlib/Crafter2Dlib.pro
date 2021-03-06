#-------------------------------------------------
#
# Project created by QtCreator 2011-09-25T11:14:59
#
#-------------------------------------------------

QT -= gui

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
    worldelement.cpp \
    commande/statusupdate.cpp \
    idset.cpp \
    message/screen/objectinformation.cpp \
    message/screen/majposition.cpp \
    message/screen/requestobjectinformation.cpp \
    inventory.cpp \
    gtree.cpp \
    message/screen/getnearbyobjects.cpp \
    message/screen/nearbyobjects.cpp \
    utils/utils.cpp \
    utils/jsonparser.cpp

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
    worldelement.hpp \
    commande/statusupdate.hpp \
    idset.hpp \
    message/screen/objectinformation.hpp \
    message/screen/majposition.hpp \
    message/screen/requestobjectinformation.hpp \
    imessagehandler.hpp \
    inventory.hpp \
    gtree.hpp \
    message/screen/getnearbyobjects.hpp \
    message/screen/nearbyobjects.hpp \
    utils/factory.hpp \
    utils/utils.hpp \
    utils/singleton.hpp \
    utils/jsonparser.hpp
