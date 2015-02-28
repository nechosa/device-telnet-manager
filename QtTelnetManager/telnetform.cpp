#include "telnetform.h"
#include "ui_telnetform.h"
#include <QDebug>

TelnetForm::TelnetForm(QWidget *parent)
        : QWidget(parent), ui(new Ui::TelnetForm)
{
    ui->setupUi(this);
    cl = new CLI();
    lled = new LED();
    lled->turnOff();

            ui->lb_login->hide();
        ui->lb_password->hide();
        ui->login_edit->hide();
        ui->password_edit->hide();

    QBoxLayout * pbxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    pbxLayout->addWidget(lled);
    ui->led->setLayout(pbxLayout);

    QVBoxLayout *vboxlayout = new QVBoxLayout();
    vboxlayout->addWidget(cl);
    ui->console->setLayout(vboxlayout);
    // Выключаем светодиод
    //led - turnOff();

    //connect(ui->ipaddr,SIGNAL(currentIndexChanged(int)),this,SLOT(checkCustomIPAddress(int)));
    //connect(ui->login_edit,SIGNAL(textChanged(QString&)),this,SLOT(
    //connect(cl,SIGNAL(onCommand(QString)),this,SIGNAL(onCommand(QString)));
    QObject::connect(cl,SIGNAL(onCommand(QString)),this,SLOT(trySlot(QString)));
    connect(ui->connect,SIGNAL(clicked()),this,SIGNAL(processConnect()));
    connect(ui->show_login_form,SIGNAL(clicked()),this,SLOT(show_login_form()));
    //connect(ui->show_login_form,SIGNAL(clicked()),this,
            //connect(ui->ipaddr,SIGNAL(currentIndexChanged(int)),this,SLOT(checkCustomIPAddress(int)));

        }

void TelnetForm::trySlot(QString message)
{
    /*
    qDebug("trySlot()");
     qDebug()<<message;*/
     emit onCommand(message);
       qDebug("onCommand()");
     qDebug()<<message;

}

void TelnetForm::show_login_form()
{
    if ((ui->lb_login->isVisible())&&(ui->lb_password->isVisible())&&(ui->login_edit->isVisible())&&(ui->password_edit->isVisible()))
    {
        ui->lb_login->hide();
        ui->lb_password->hide();
        ui->login_edit->hide();
        ui->password_edit->hide();
    }
    else
    {
        ui->lb_login->show();
        ui->lb_password->show();
        ui->login_edit->show();
        ui->password_edit->show();
    }

   // qDebug("tryConnect()");
}

QString TelnetForm::getIPAddress() const
{
    return ui->ipaddr->currentText();
}

/*
void TelnetForm::setIPAddress(QString password)
{
    ui->ipaddr->setCurrentIndex();
}

*/
QString TelnetForm::getPassword() const
{
    return ui->password_edit->text();
}

void TelnetForm::setPassword(QString password)
{
    ui->password_edit->setText(password);
}

QString TelnetForm::getLogin() const
{
    return ui->login_edit->text();
}

void TelnetForm::setLogin(QString login)
{
    ui->login_edit->setText(login);
}

/*
void TelnetForm::setEnableLogin(bool enable)
{
    ui->login_edit->setEnabled(enable);
}

void TelnetForm::setEnablePassword(bool enable)
{
     ui->password_edit->setEnabled(enable);
}

void TelnetForm::setEnableIPAddressBox(bool enable)
{
     ui->ipaddr->setEnabled(enable);
}

void TelnetForm::ledOn(bool on)
{
    lled->turnOff(on);

}
void TelnetForm::setTitleButton(QString title)
{
    ui->connect->setText(title);
}

void TelnetForm::checkCustomIPAddress(int idx)
{
    Q_UNUSED(idx);
    emit processIPAddressChanged(ui->ipaddr->currentText());
}
*/

void TelnetForm::ledOn(bool on)
{
    lled->turnOff(on);

}
TelnetForm::~TelnetForm()
{
    delete ui;
}
