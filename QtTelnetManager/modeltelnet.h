#ifndef MODELTELNET_H
#define MODELTELNET_H

#include "telnetthread.h"
#include <QList>
class ModelTelnet
{
public:
    ModelTelnet();
    ~ModelTelnet();



    //void setStatus(const QString &st);
    void setLogin(const QString &login);
    void setPassword(const QString &password);

    //QString getStatus() const ;
    QString getLogin() const ;
    QString getPassword() const ;

    //Соединение с Telnet
    void connectToTelnet(const QString &ipaddr,const QString &login,const QString &password);

    //Адрес
    /*
    void setIPAddress (QString ipaddr);
    QString getIPAddress() const;
    */

    //получение состояния telnet
    bool isConnect() const;

    //Запись в Telnet
    void onCommand(QString command);

    //Приём ответа из Telnet
  //  void response(QString msg);
    //QList<QString> getListIPAddress();

private:
    //
    //void searchIpAddress()
    //отправка команды в контроллер
   // void sendCommand(QString command);



    //Разбор принятой программы
    //void evalutateCommand(quint8 cmd);

private:
    bool t_connected; // Есть ли соединение Telnet
    QString t_ipaddr;
   // QList <QString> t_listIPAddress; //Список IP адресов на форме

    QString t_login;
    QString t_password;

    QString t_msg;

    QString t_command;


    /*QString t_msg;
    QString t_status;//int*/

    /*
    QByteArray m_inBuf;
    */
    TelnetThread* thread;

};

#endif // MODELTELNET_H
