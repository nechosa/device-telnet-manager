# -------------------------------------------------
# Project created by QtCreator 2015-02-19T10:15:51
# -------------------------------------------------
QT += network \
    opengl \
    sql \
    svg \
    xml \
    xmlpatterns
TARGET = qttelnetmanager
TEMPLATE = app
SOURCES += main.cpp \
    mainform.cpp \
    field.cpp \
    device.cpp
HEADERS += mainform.h \
    field.h \
    device.h
FORMS += mainform.ui
RESOURCES += resourses.qrc

include(QtTelnetManager/QtTelnetManager.pri)
