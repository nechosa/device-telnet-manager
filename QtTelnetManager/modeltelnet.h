#ifndef MODELTELNET_H
#define MODELTELNET_H

#include "telnetthread.h"

class ModelTelnet
{
public:
    ModelTelnet();
    ~ModelTelnet();

    //���������� � Telnet
    void connectToTelnet();

    //�����
    void setIPAddress (QString ipaddr);
    QString getIPAddress() const;

    //��������� ��������� telnet
    bool isConnect() const;

    //������ � Telnet
    void onCommand(QString command);

    //��ɣ� ������ �� Telnet
    void response(QByteArray msg);

private:
    //�������� ������� � ����������
    void sendCommand(int command);

    //������ �������� ���������
    //void evalutateCommand(quint8 cmd);

private:
    bool t_connected; // ���� �� ���������� Telnet
    QString t_ipaddr;
    //int
    QByteArray m_inBuf;
    TelnetThread* thread;
};

#endif // MODELTELNET_H
