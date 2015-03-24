# -------------------------------------------------
# Project created by QtCreator 2015-02-19T10:15:51
# -------------------------------------------------
QT += network \
    opengl \
    sql \
    svg \
    xml \
    core \
    xmlpatterns
TARGET = qttelnetmanager
TEMPLATE = app
SOURCES += main.cpp \
    mainform.cpp \
    field.cpp \
    device.cpp \
    msgbox.cpp
HEADERS += mainform.h \
    field.h \
    device.h \
    msgbox.h \
    const.h
FORMS += mainform.ui
CONFIG += core

# warn_on
QMAKE_CFLAGS_WARN_ON = -W2
RESOURCES += resourses.qrc
include(QtTelnetManager/QtTelnetManager.pri)
HEADERS += constant.h
