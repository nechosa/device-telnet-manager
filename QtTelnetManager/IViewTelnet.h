#ifndef IVIEWTELNET_H
#define IVIEWTELNET_H

#include "modeltelnet.h"

class IViewTelnet
{
public:
    // Имя
    virtual QString getIPAddress() const = 0;
    virtual setIPAddress(QString ipaddr) = 0;

    //virtual void addIPAddress(QString ipaddr);

    //Включение/Выключение светодиода
    virtual void ledOn(bool on) = 0;

    //Блокировка combobox
    virtual void setEnableIPAddressBox(bool enable) = 0;

    //Изменение надписи на кнопке
    virtual void setTitleButton(QString) = 0;

    //signals
public:
    //Подключение к Telenet
    virtual void processConnect() = 0;

    //Изменение IP адреса
    virtual void processIPAddressChanged(QString ipaddr);

    //Отправка данных в Telnet
    virtual void onCommand(QString command) = 0;
};

#endif // IVIEWTELNET_H
