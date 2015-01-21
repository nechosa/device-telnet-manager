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

    //����� �������� ����������
    virtual QString getIPAddress() const;
    //virtual void setIPAddress(QString ipaddr); ����������� �����!!!

    //���������/ ���������� ����������
    virtual void ledOn(bool on);

    //���������� comboBox
    virtual void setEnableIPAddress(bool enable);

    //��������� ������� �� ������
    virtual void setTitleButton(QString title);

private slots:
    void checkCustomIPAddress(int idx);

signals:
    //����������� � Telnet
    void processConnect();
    //��������� IP ������
    void processIPAddressChanged(QString ipaddr);

    //�������� ������� � Telnet
    void onCommand(QString cmd);

private:
    Ui::TelnetForm *ui;
};

#endif // TELNETFORM_H
