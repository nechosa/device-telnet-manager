#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QtGui/QLineEdit>


#include "qttelnet.h"

class LoginDialog : public QDialog
{
public:
    LoginDialog(QWidget *parent = 0);
    private:

    QLineEdit *lle;

    QLineEdit *ple;

    public:
    QString login() const { return lle->text(); }
    QString password() const { return ple->text(); }


};

#endif // LOGINDIALOG_H
