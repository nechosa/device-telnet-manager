#ifndef MODELTELNET_H
#define MODELTELNET_H

#include "telnetthread.h"

class ModelTelnet
{
public:
    ModelTelnet();
    ~ModelTelnet();

    //Соединение с Telnet
    void connectToTelnet();

    //Адрес
    void setIPAddress (QString ipaddr);
    QString getIPAddress() const;

    //получение состояния telnet
    bool isConnect() const;

    //Запись в Telnet
    void onCommand(QString command);

    //Приём ответа из Telnet
    void response(QByteArray msg);

private:
    //отправка команды в контроллер
    void sendCommand(int command);

    //Разбор принятой программы
    //void evalutateCommand(quint8 cmd);

private:
    bool t_connected; // Есть ли соединение Telnet
    QString t_ipaddr;
    //int
    QByteArray m_inBuf;
    TelnetThread* thread;
};

#endif // MODELTELNET_H
