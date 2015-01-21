# -------------------------------------------------
# Project created by QtCreator 2015-01-20T10:04:18
# -------------------------------------------------
QT += network
TARGET = QtTelnetManager
TEMPLATE = app
include(../src/qttelnet.pri)
SOURCES += main.cpp \
    telnetform.cpp \
    modeltelnet.cpp \
    telnetthread.cpp \
    presentertelnet.cpp
HEADERS += telnetform.h \
    IViewTelnet.h \
    modeltelnet.h \
    telnetthread.h \
    presentertelnet.h
FORMS += telnetform.ui
