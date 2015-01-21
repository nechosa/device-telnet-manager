# -------------------------------------------------
# Project created by QtCreator 2015-01-14T14:11:06
# -------------------------------------------------
QT += network
TARGET = TelnetManager
TEMPLATE = app

include(../src/qttelnet.pri)

SOURCES += main.cpp \
    mainwindow.cpp \
    telnetclient.cpp \
    cli.cpp \
    logindialog.cpp
HEADERS += mainwindow.h \
    telnetclient.h \
    cli.h \
    logindialog.h
FORMS += mainwindow.ui
