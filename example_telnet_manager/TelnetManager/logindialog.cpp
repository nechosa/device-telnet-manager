#include "logindialog.h"
#include <QtGui/QApplication>
#include <QtGui/QTextEdit>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QInputDialog>
#include <QtGui/QFont>
#include <QtCore/QEvent>
#include <QtGui/QShortcut>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QDialog>
#include <QtGui/QLayout>
#include <QtGui/QKeyEvent>
#include <QtGui/QScrollBar>

LoginDialog::LoginDialog(QWidget *parent)
        : QDialog(parent)
    {
        QGridLayout *gl = new QGridLayout;
        setLayout(gl);

        QLabel *l;

        l = new QLabel("&Login:", this);
        gl->addWidget(l, 0, 0);
        lle = new QLineEdit(this);
        gl->addWidget(lle, 0, 1);
        l->setBuddy(lle);

        l = new QLabel("&Password:", this);
        gl->addWidget(l, 1, 0);
        ple = new QLineEdit(this);
        ple->setEchoMode(QLineEdit::Password);
        gl->addWidget(ple, 1, 1);
        l->setBuddy(ple);

        QWidget *hbox = new QWidget(this);
        QHBoxLayout *hboxlayout = new QHBoxLayout;

        gl->addWidget(hbox, 2, 0, 1, 2);

        QPushButton *pb;
        pb = new QPushButton("&Ok");
        connect(pb, SIGNAL(clicked()), this, SLOT(accept()));
        hboxlayout->addWidget(pb);

        pb = new QPushButton("&Cancel");
        connect(pb, SIGNAL(clicked()), this, SLOT(reject()));
        hboxlayout->addWidget(pb);

        hbox->setLayout(hboxlayout);
    }
