#ifndef IVIEWTELNET_H
#define IVIEWTELNET_H

#include "modeltelnet.h"

class IViewTelnet
{
public:
    // ���
    virtual QString getIPAddress() const = 0;
    virtual setIPAddress(QString ipaddr) = 0;

    //virtual void addIPAddress(QString ipaddr);

    //���������/���������� ����������
    virtual void ledOn(bool on) = 0;

    //���������� combobox
    virtual void setEnableIPAddressBox(bool enable) = 0;

    //��������� ������� �� ������
    virtual void setTitleButton(QString) = 0;

    //signals
public:
    //����������� � Telenet
    virtual void processConnect() = 0;

    //��������� IP ������
    virtual void processIPAddressChanged(QString ipaddr);

    //�������� ������ � Telnet
    virtual void onCommand(QString command) = 0;
};

#endif // IVIEWTELNET_H
