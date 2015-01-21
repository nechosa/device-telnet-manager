#ifndef TELNETFORM_H
#define TELNETFORM_H

#include <QtGui/QWidget>
//#include "itelnetview"
namespace Ui
{
    class TelnetForm;
}

class TelnetForm : public QWidget
{
    Q_OBJECT

public:
    TelnetForm(QWidget *parent = 0);
    ~TelnetForm();

    //Адрес текущего соединения
    virtual QString getIPAddress() const;
    //virtual void setIPAddress(QString ipaddr); реализовать позже!!!

    //Включение/ выключение светодиода
    virtual void ledOn(bool on);

    //Блокировка comboBox
    virtual void setEnableIPAddress(bool enable);

    //Изменение надписи на кнопке
    virtual void setTitleButton(QString title);

private slots:
    void checkCustomIPAddress(int idx);

signals:
    //Подключение к Telnet
    void processConnect();
    //Изменение IP адреса
    void processIPAddressChanged(QString ipaddr);

    //Отправка команды в Telnet
    void onCommand(QString cmd);

private:
    Ui::TelnetForm *ui;
};

#endif // TELNETFORM_H
