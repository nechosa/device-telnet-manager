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

    //���������� � Telnet
    void connectToTelnet(const QString &ipaddr,const QString &login,const QString &password);

    //�����
    /*
    void setIPAddress (QString ipaddr);
    QString getIPAddress() const;
    */

    //��������� ��������� telnet
    bool isConnect() const;

    //������ � Telnet
    void onCommand(QString command);

    //��ɣ� ������ �� Telnet
  //  void response(QString msg);
    //QList<QString> getListIPAddress();

private:
    //
    //void searchIpAddress()
    //�������� ������� � ����������
   // void sendCommand(QString command);



    //������ �������� ���������
    //void evalutateCommand(quint8 cmd);

private:
    bool t_connected; // ���� �� ���������� Telnet
    QString t_ipaddr;
   // QList <QString> t_listIPAddress; //������ IP ������� �� �����

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
