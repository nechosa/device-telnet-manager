#include "property.h"
#include "ui_property.h"

Property::Property(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Property)
{
    m_ui->setupUi(this);
}

Property::~Property()
{
    delete m_ui;
}

void Property::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void Property::setName(const QString & p_name)
{
    m_ui->txtName->setText(p_name);
}
