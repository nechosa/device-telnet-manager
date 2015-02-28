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

    //Подключение к Telnet порту
    void processConnect();
   void onCommand(QString command);
/*
public slots:
    void onCommand(QString command);
    */
    
/*
    //Измение адреса хоста
    //void processHostChanged(QString ipaddr);

    // изменение параметров авторизиции  - логина и пароля
    //void proccessAuthChanged(QString login, QString password);

    //Отправка в Телнет


    //Получение ответа из Телнет
   // void response(const QString &msg);

    //Истекло время ожидания ответа
    //void timeout(QString timeoutMsg);

    //ошибка отправки сообщения
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
