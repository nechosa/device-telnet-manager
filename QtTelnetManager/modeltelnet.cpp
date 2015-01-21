#include "modeltelnet.h"
#include <QDebug>

ModelTelnet::ModelTelnet()
{
    thread = TelnetThread::getInstanse();
}
ModelTelnet::~ModelTelnet(){
    qDebug("~ModelTelnet");
    if (thread)
    {
        thread->free();
        thread = 0;
    }
}
ModelTelnet::connectToTelnet()
{
    if (t_connected)
    {
        if (t_ipaddr=="")
        {
            return;
        }
        if (!thread->isRunning())
        {
            thread->connectTelnet();

            //в случае успешного подключения
            if (thread->isConnect())
            {
                t_connected = true;
            }
        }
    }
    else
    {
        if (thread->isConnect())
        {
            thread->disconnectTelnet();
        }
        t_connected = false;
    }
}
