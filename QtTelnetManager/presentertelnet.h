#ifndef PRESENTERTELNET_H
#define PRESENTERTELNET_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include "modeltelnet.h"
#include "IViewTelnet.h"
#include "telnetthread.h"

//template <typename T> class QList;

class PresenterTelnet : public QObject
{
    Q_OBJECT
public:
    explicit PresenterTelnet(IViewTelnet *view,QObject *parent = 0);
    ~PresenterTelnet();

    //void appendView(IViewTelnet *view);


private slots:

    //����������� � Telnet �����
    void processConnect();
   void onCommand(QString command);
/*
public slots:
    void onCommand(QString command);
    */
    
/*
    //������� ������ �����
    //void processHostChanged(QString ipaddr);

    // ��������� ���������� �����������  - ������ � ������
    //void proccessAuthChanged(QString login, QString password);

    //�������� � ������


    //��������� ������ �� ������
   // void response(const QString &msg);

    //������� ����� �������� ������
    //void timeout(QString timeoutMsg);

    //������ �������� ���������
    //void error(QString errorMsg);
*/
private:

    void refreshView() const;
   /*
    void refreshView(IViewTelnet *view) const;
    void setTelnetInfo() const;
    void setTelnetInfo(IViewTelnet *view) const;
    */

private:
    ModelTelnet *t_model;
    IViewTelnet *t_view;

//    TelnetThread* thread;
};

#endif // PRESENTERTELNET_H
