#include <QtGui/QApplication>
#include "presentertelnet.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TelnetForm w;
    PresenterTelnet *presenterTelnet = new PresenterTelnet();
    presenterTelnet->appendView(&w);
    w.show();
    return a.exec();
}
