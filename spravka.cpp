/********************************************************
* ��� �����: spravka.cpp
* ���������� ������: ������� � ��������� (����������)
* �����: Zakharov
* ���� ��������:           2013/19/06
* ���� ��������� ��������: 2013/19/06
*********************************************************/

#include "spravka.h"
#include "ui_spravka.h"
#include "QDateTime"

spravka::spravka(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::spravka)
{
    ui->setupUi(this);
}

spravka::~spravka()
{
    delete ui;
}

void spravka::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

