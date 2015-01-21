#include "telnetclient.h"
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

TelnetClient::TelnetClient(QMainWindow *par)
    : QMainWindow(par), t(new QtTelnet)
{
     //t->setPromptString("Welcome");

        QWidget *vbox = new QWidget(this);
        QVBoxLayout *vboxlayout = new QVBoxLayout();

        //textEdit = new QTextEdit();
        textEdit = new CLI();
        lineEdit = new QLineEdit();
        status = new QLabel();
        quit = new QPushButton("Quit");
        connect(quit, SIGNAL(clicked()), this, SLOT(close()));

        vboxlayout->addWidget(textEdit);
        vboxlayout->addWidget(lineEdit);
        vboxlayout->addWidget(status);
        vboxlayout->addWidget(quit);
        vbox->setLayout(vboxlayout);
        this->setCentralWidget(vbox);

        QFont fnt = textEdit->font();
        fnt.setFamily("Fixed");
        textEdit->setFont(fnt);

        lineEdit->installEventFilter(this);
        installEventFilter(this);

        QShortcut *shortcut;

        shortcut = new QShortcut(this);
        shortcut->setKey(Qt::CTRL + Qt::Key_D);
        connect(shortcut, SIGNAL(activated()),
                this, SLOT(deleteCharOrLogout()));

        shortcut = new QShortcut(this);
        shortcut->setKey(Qt::CTRL + Qt::Key_Z);
        connect(shortcut, SIGNAL(activated()), this, SLOT(suspend()));

        shortcut = new QShortcut(this);
        shortcut->setKey(Qt::CTRL + Qt::Key_C);
        connect(shortcut, SIGNAL(activated()), this, SLOT(kill()));

        textEdit->setReadOnly(true);

        connect(lineEdit, SIGNAL(returnPressed()),
                this, SLOT(lineReturnPressed()));

        connect(t, SIGNAL(message(const QString &)),
                this, SLOT(telnetMessage(const QString &)));
        connect(t, SIGNAL(loginRequired()),
                this, SLOT(telnetLoginRequired()));
        connect(t, SIGNAL(loginFailed()),
                this, SLOT(telnetLoginFailed()));
        connect(t, SIGNAL(loggedOut()),
                this, SLOT(telnetLoggedOut()));
        connect(t, SIGNAL(loggedIn()),
                this, SLOT(telnetLoggedIn()));
        connect(t, SIGNAL(connectionError(QAbstractSocket::SocketError)),
                this, SLOT(telnetConnectionError(QAbstractSocket::SocketError)));

        QString host = QInputDialog::getText(this,
                                             "Host name",
                                             "Host name of Telnet server",
                                             QLineEdit::Normal,
                                             "localhost");
        host = host.trimmed();
        if (!host.isEmpty())
            t->connectToHost(host);
        else
            textEdit->setPlainText("Not connected");
}

   // virtual void TelnetClient::resizeEvent(QResizeEvent *ev)

   // bool TelnetClient::eventFilter(QObject *obj, QEvent *event)
/*
    void TelnetClient::telnetMessage(const QString &msg)
    {

    }
    */
    /*
    TelnetClient::telnetLoginRequired()
    {

    }
    */
    /*
    void TelnetClient::telnetLoginFailed()
    {
        status->setText("Login failed");
    }
    */
    /*
    void TelnetClient::telnetLoggedOut()
    {
    }
    void TelnetClient::telnetLoggedIn()
    {

    }
    void TelnetClient::telnetConnectionError(QAbstractSocket::SocketError error)
    {

    }
    void TelnetClient::suspend()
    {

    }

    void TelnetClient::kill()
    {

    }
    void TelnetClient::lineReturnPressed()
    {

    }
    void TelnetClient::deleteCharOrLogout()
    {

    }
    */
    /*
    QString TelnetClient::stripCR(const QString &msg)
    {

    }
    */
