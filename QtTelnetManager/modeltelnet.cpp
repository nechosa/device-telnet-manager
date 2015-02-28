#include "modeltelnet.h"

#include <QDebug>

ModelTelnet::ModelTelnet()
{
    //thread = TelnetThread::getInstance();
    t_ipaddr="";
    t_login="";
    t_password="";
    t_connected = false;

}

ModelTelnet::~ModelTelnet(){
    qDebug("~ModelTelnet");
    /*
    if (thread)
    {
        thread->free();
        thread = 0;
    }
    */
}

void ModelTelnet::connectToTelnet(const QString &ipaddr,const QString &login,const QString &password)
{
     qDebug("ModelTelnet::connectToTelnet()");
     t_ipaddr = ipaddr;
     t_login = login;
     t_password = password;
     t_connected = true;
     /*
     qDebug(t_connected);
     qDebug(t_login);
     */
     qDebug() <<"t_connected" <<t_connected;
     qDebug() <<"t_login"<< t_login;
     qDebug() <<"t_login"<< t_ipaddr;
     qDebug() <<"t_password"<< t_password;


    /*
    if (t_connected)
    {
        if (t_ipaddr=="")
        {
            return;
        }
        if (!thread->isRunning())
        {
            thread->connectTelnet(t_ipaddr,t_login,t_password);

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
    */
}


bool ModelTelnet::isConnect() const
{
    return t_connected;
}
void ModelTelnet::onCommand(QString command)
{
       qDebug() <<"command1234" <<command;
    //sendCommand(command);
     qDebug(" ModelTelnet::onCommand - sendCommand");
}
/*
void ModelTelnet::response(QString msg)
{
    t_msg = msg;
    //Разбор пришедшего пакета
}
void ModelTelnet::sendCommand(QString command)
{
    thread->transaction(command,250);
}
*/

void ModelTelnet::setLogin(const QString &login)
{
    t_login = login;
}

QString ModelTelnet::getLogin() const
{
    return t_login;
}

void ModelTelnet::setPassword(const QString &password)
{
    t_password = password;
}

QString ModelTelnet::getPassword() const
{
    return t_password;
}
/*
*/
/*
QList <QString> ModelTelnet::getListIPAddress()
{
    return t_listIPAddress;
}
*/
/*
void ModelTelnet::searchIPAddr()
{

    foreach(const )
       t_listIPAddres.append();

}*/
