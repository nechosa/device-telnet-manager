#include "telnetform.h"
#include "ui_telnetform.h"

TelnetForm::TelnetForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::TelnetForm)
{
    ui->setupUi(this);
    // Выключаем светодиод
    //led - turnOff();
}

void TelnetForm::getIPAddress() const
{
    return ui->ipaddr->currentText();
}
/*
TelnetForm::addIPAddress(QString ipaddr)
{
    ui->ipaddr->setCurrentIndex()
}
*/
void TelnetForm::checkCustomIPAddress(int idx)
{
    Q_UNUSED(idx);
    emit processIPAddressChanged(ui->ipaddr->currentText());
}

TelnetForm::~TelnetForm()
{
    delete ui;
}
