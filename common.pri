infile(config.pri, SOLUTIONS_LIBRARY, yes): CONFIG += qttelnet-uselib
TEMPLATE += fakelib
QTTELNET_LIBNAME = $$qtLibraryTarget(QtTelnet)
TEMPLATE -= fakelib
QTTELNET_LIBDIR = $$PWD/lib
unix:qttelnet-uselib:!qttelnet-buildlib:QMAKE_RPATHDIR += $$QTTELNET_LIBDIR
