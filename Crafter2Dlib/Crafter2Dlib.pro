#-------------------------------------------------
#
# Project created by QtCreator 2011-09-25T11:14:59
#
#-------------------------------------------------

QT       += network

TARGET = Crafter2Dlib
TEMPLATE = lib

DEFINES += CRAFTER2DLIB_LIBRARY

SOURCES += crafter2dlib.cpp

HEADERS += crafter2dlib.hpp\
        Crafter2Dlib_global.hpp

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE57A0257
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = Crafter2Dlib.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
