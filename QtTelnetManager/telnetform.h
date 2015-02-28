#ifndef TELNETFORM_H
#define TELNETFORM_H

#include <QtGui/QWidget>
#include "IViewTelnet.h"
#include "cli.h"
#include "led.h"

namespace Ui
{
    class TelnetForm;
}

class TelnetForm : public QWidget, public IViewTelnet
{
    Q_OBJECT

public:
    TelnetForm(QWidget *parent = 0);
    ~TelnetForm();

    //Адрес текущего соединения
    virtual QString getIPAddress() const;
    /**/
    virtual QString getLogin() const;
    virtual QString getPassword() const;


    /*virtual void setIPAddress(QString ipaddr);*/
    virtual void setLogin(QString login);
    virtual void setPassword(QString password);
/*

    virtual void setIPAddress(QString ipaddr); реализовать позже!!!
*/
    //Включение/ выключение светодиода
    virtual void ledOn(bool on);

    //Блокировка comboBox
    //virtual void setEnableIPAddressBox(bool enable);
        //Блокировка Login
    //virtual void setEnableLogin(bool enable);

    //Блокировка Password
    //virtual void setEnablePassword(bool enable);

    //Изменение надписи на кнопке
    //virtual void setTitleButton(QString title);

private slots:
    //void checkCustomIPAddress(int idx);
    public slots:
        void show_login_form();
       void trySlot(QString message);
    //void checkCustomIPAddress(int idx);

signals:
    //Подключение к Telnet
    void processConnect();
    //Изменение IP адреса
    //void processIPAddressChanged(QString ipaddr);
    //void proccessLoginChanged(QString login);
    //void proccessPasswordChanged(QString password);

   // void processAuthChanged(QString login,QString password);

    //Отправка команды в Telnet
    void onCommand(QString command);

private:
    Ui::TelnetForm *ui;
    CLI *cl;
    LED *lled;
};

#endif // TELNETFORM_H
