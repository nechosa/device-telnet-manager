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
    spravka.cpp \
    mainform.cpp \
    field.cpp \
    device.cpp \
    msgbox.cpp \
    property.cpp \
    link.cpp \
    text.cpp
HEADERS += mainform.h \
    spravka.h \
    field.h \
    device.h \
    msgbox.h \
    const.h \
    property.h \
    link.h \
    text.h
FORMS += mainform.ui \
    spravka.ui \
    property.ui
CONFIG += core

# warn_on
QMAKE_CFLAGS_WARN_ON = -W2
RESOURCES += resourses.qrc
include(QtTelnetManager/QtTelnetManager.pri)
HEADERS += constant.h
