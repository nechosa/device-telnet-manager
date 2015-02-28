#ifndef TELNETTHREAD_H
#define TELNETTHREAD_H

#include <QThread>
#include <QMutex>
#include <QString>
#include <QWaitCondition>
#include "qttelnet.h"

class TelnetThread : public QThread
{
    Q_OBJECT



public:
    static TelnetThread* getInstance();

    void run();
    void transaction(const QString &msg, int waitTimeout);
    void connectTelnet(QString ipaddr,QString login,QString password);
    void disconnectTelnet();
    bool isConnect();
    void free();

    void setStatus(const QString &st);
    /*
    void setLogin(const QString &login);
    void setPassword(const QString &password);
        */
    QString getStatus() const;
    /*
    QString getLogin() const;
    QString getPassword() const;
    */



signals:
    void responseMsg(const QString &s);
    void error(const QString &s);
    void timeout(const QString &s);


private:
    TelnetThread(QObject *parent = 0);
    ~TelnetThread();
    TelnetThread(const TelnetThread&);
    TelnetThread& operator=(const TelnetThread&);

private:
    int t_waitTimeout;
    QMutex mutex;

    QWaitCondition cond;

    QString t_ipaddr;
    QString t_login;
    QString t_password;
    QString t_msg;
    QString t_status;

    QByteArray t_request;

    QtTelnet *t;

    bool t_isConnect;
    bool t_isDisconnecting;
    bool t_isConnecting;
    bool t_isQuit;

    static TelnetThread* t_instance;
    static int t_refCount;

    private:
    QString stripCR(const QString &msg);

    private slots:
        void telnetMessage(const QString &msg);
        void telnetLoginRequired();
        void telnetLoginFailed();
        void telnetLoggedOut();
        void telnetLoggedIn();
        void telnetConnectionError(QAbstractSocket::SocketError error);
        void suspend();
        void kill();
        void lineReturnPressed();
        //void deleteCharOrLogout();




};

#endif // TELNETTHREAD_H
