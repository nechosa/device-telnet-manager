
#include <QtGui/QApplication>
#include "mainwindow.h"


#include "qttelnet.h"
#include "telnetclient.h"
#include "logindialog.h"


int main( int argc, char **argv )
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    TelnetClient t;
    t.show();
    return a.exec();
}


