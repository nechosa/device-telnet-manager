INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
include(src/qttelnet.pri)

SOURCES +=  \
    QtTelnetManager/telnetform.cpp \
    QtTelnetManager/modeltelnet.cpp \
    QtTelnetManager/telnetthread.cpp \
    QtTelnetManager/presentertelnet.cpp \
    QtTelnetManager/cli.cpp \
    QtTelnetManager/led.cpp
HEADERS +=  \
    QtTelnetManager/telnetform.h \
    QtTelnetManager/IViewTelnet.h \
    QtTelnetManager/modeltelnet.h \
    QtTelnetManager/telnetthread.h \
    QtTelnetManager/presentertelnet.h \
    QtTelnetManager/cli.h \
    QtTelnetManager/led.h
FORMS +=  QtTelnetManager/telnetform.ui

