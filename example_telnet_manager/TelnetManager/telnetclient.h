#ifndef TELNETCLIENT_H
#define TELNETCLIENT_H

#include <QMainWindow>
#include "logindialog.h"
#include "qttelnet.h"
#include "cli.h"
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

class TelnetClient : public QMainWindow
{
     Q_OBJECT
public:
    TelnetClient(QMainWindow *par = 0);

protected:
    void resizeEvent(QResizeEvent *ev)
     {
        QFontMetrics fm(font());
        int lh = fm.lineSpacing();
        int cw = fm.width(QChar('X'));
        QRect r = textEdit->visibleRegion().boundingRect();
        int dx = ev->oldSize().width() - r.width();
        int dy = ev->oldSize().height() - r.height();

        t->setWindowSize((ev->size().width() - dx) / cw,
                         (ev->size().height() - dy) / lh);
    }
    bool eventFilter(QObject *obj, QEvent *event)
     {
        if (event->type() == QEvent::ShortcutOverride) {
            QKeyEvent *ke = static_cast<QKeyEvent *>(event);
            if (ke->modifiers() & Qt::ControlModifier) {
                switch (ke->key()) {
                case Qt::Key_C:
                case Qt::Key_D:
                case Qt::Key_Z:
                    return true;
                default:
                    break;
                }
            }
        }
        return QObject::eventFilter(obj, event);
    }

private slots:
    void telnetMessage(const QString &msg)
    {
         textEdit->append(stripCR(msg));
        QScrollBar *s = textEdit->verticalScrollBar();
        s->setValue(s->maximum());
    }
    void telnetLoginRequired()
    {

    LoginDialog ld(this);
        if (ld.exec() == LoginDialog::Accepted)
            t->login(ld.login(), ld.password());
        else
            t->logout();
    }
    void telnetLoginFailed()
    {
         status->setText("Login failed");
    }
    void telnetLoggedOut()
    {

        lineEdit->setEnabled(false);
        status->setText("Logged out");
    }
    void telnetLoggedIn()
    {
        lineEdit->setEnabled(true);
        status->setText("Logged in");
    }
    void telnetConnectionError(QAbstractSocket::SocketError error)
    {
        status->setText(QString("Connection error: %1").arg(error));
    }
    void suspend()
    {
         t->sendControl(QtTelnet::Suspend);
    }
    void kill()
    {
         t->sendControl(QtTelnet::InterruptProcess);
    }
    void lineReturnPressed()
    {
         t->sendData(lineEdit->text());
        lineEdit->clear();
    }
    void deleteCharOrLogout()
    {
        if (lineEdit->text().isEmpty()) {
            t->logout();
        } else {
            int cpos = lineEdit->cursorPosition();
            QString txt = lineEdit->text();
            if (cpos < (int)txt.length()) {
                lineEdit->setText(txt.remove(cpos, 1));
                lineEdit->setCursorPosition(cpos);
            }
        }
    }

private:
    QString stripCR(const QString &msg)
    {
         QString nmsg(msg);
        nmsg.remove('\r');
        nmsg.remove(QRegExp("\033\\[[0-9;]*[A-Za-z]")); // Also remove terminal control codes
        return nmsg;
    }

private:
    QtTelnet *t;
    /*
    CLI *cl;
    QTextEdit *textEdit;
    */
    CLI *textEdit;
    // QTextEdit *textEdit;

    QLineEdit *lineEdit;
    QLabel *status;
    QPushButton *quit;
};

#endif // TELNETCLIENT_H
