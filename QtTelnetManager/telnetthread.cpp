#include "telnetthread.h"
#include "qttelnet.h"
#include <QTime>
#include <QDebug>

TelnetThread* TelnetThread::t_instance = 0;
int TelnetThread::t_refCount = 0;

TelnetThread::TelnetThread(QObject * parent)
        :QThread(parent),
        t_waitTimeout(0),
        t_isQuit(false),
        t_isConnect(false),
        t_isDisconnecting(false),
        t_isConnecting(false),
        t(new QtTelnet())
{
    //t = new QtTelnet();
    QMutexLocker locker(&mutex);

    connect(t, SIGNAL(message(const QString &)),this, SLOT(telnetMessage(const QString &)));
    connect(t, SIGNAL(loginRequired()),this, SLOT(telnetLoginRequired()));
    connect(t, SIGNAL(loginFailed()),this, SLOT(telnetLoginFailed()));
    connect(t, SIGNAL(loggedOut()),this, SLOT(telnetLoggedOut()));
    connect(t, SIGNAL(loggedIn()),this, SLOT(telnetLoggedIn()));
    connect(t, SIGNAL(connectionError(QAbstractSocket::SocketError)),this, SLOT(telnetConnectionError(QAbstractSocket::SocketError)));

}

TelnetThread::~TelnetThread()
{
    mutex.lock();
    t_isQuit = true;
    t_isConnect = false;
    t_instance = 0;
    cond.wakeOne();
    qDebug("TelnetThread()");
    mutex.unlock();
    wait();
}

void TelnetThread::connectTelnet(QString ipaddr,QString login,QString password)
{
    t_ipaddr = ipaddr;
    t_login = login;
    t_password = password;

    //Если поток не запущен - запускаем его
    if(!isRunning())
    {
        t_isConnecting = true;
        start();
        t_isQuit = false;
    }
    else
    {
        //Если поток запущен будим его
        cond.wakeOne();
    }
}

void TelnetThread::disconnectTelnet()
{
    mutex.lock();
    t_isDisconnecting = true;
    mutex.unlock();
    cond.wakeOne();
}

//Отправка сообщения в телнет
void TelnetThread::transaction(const QString &msg,int waitTimeout)
{
    if (t_isConnect)
    {
        t_msg = msg;
        t_waitTimeout = waitTimeout;
    }
    // t->sendData(msg);
}


//Работа потока
void TelnetThread::run()
{

    //
    mutex.lock();
    QString host = "172.16.22.109";//t_ipaddr;
    //
    QString message = t_msg;

    mutex.unlock();
    while(!t_isQuit)
    {
        if (t_isConnecting)
        {
            if (!host.isEmpty())
                t->connectToHost(host);
        }
        else if (t_isDisconnecting)
        {
            t->close();
            t_isDisconnecting = false;
            t_msg.clear();
            t_isQuit = true;
        }
        else
        {
            //Отправляем в Telnet команду
            if (!t_msg.isEmpty())
            {
                t->sendData(message);
            }
            else
            {
                mutex.lock();
                //Засыпаем до следующей отправки
                cond.wait(&mutex);
                message = t_msg;
                mutex.unlock();
            }
        }
    }
}

TelnetThread* TelnetThread::getInstance()
{
    static QMutex mutex;
    if (!t_instance)
    {
        mutex.lock();
        if (!t_instance)
        {
            t_instance = new TelnetThread;
        }

        t_refCount++;
        mutex.unlock();
    }

    return t_instance;
}

void TelnetThread::telnetMessage(const QString & msg)
{
    emit responseMsg(stripCR(msg));
}

QString TelnetThread::stripCR(const QString &msg)
{
    QString nmsg(msg);
    nmsg.remove('\r');
    nmsg.remove(QRegExp("\033\\[[0-9;]*[A-Za-z]")); // Also remove terminal control codes
    return nmsg;
}

void TelnetThread::telnetConnectionError(QAbstractSocket::SocketError error)
{
    setStatus(QString("Connection error: %1").arg(error));
}

void TelnetThread::setStatus(const QString &st)
{
    t_status = st;
}
/*
QString TelnetThread::getLogin() const
{
    return t_status;
}
*/
void TelnetThread::telnetLoginRequired()
{
    //t->login(this->getLogin(), this->getPassword());
    t->login("admin", "admin");
    //t->logout();
}

void TelnetThread::telnetLoginFailed()
{
    setStatus("Login failed");
}

void TelnetThread::telnetLoggedOut()
{
    setStatus("Logged out");
}

void TelnetThread::telnetLoggedIn()
{
    setStatus("Logged in");
}

void TelnetThread::suspend()
{
    t->sendControl(QtTelnet::Suspend);
}

void TelnetThread::kill()
{
    t->sendControl(QtTelnet::InterruptProcess);
}

void TelnetThread::lineReturnPressed()
{
    t->sendData(t_msg);
}

/*
void TelnetThread::setLogin(const QString &login)
{
    t_login = login;
}
*/

/*
QString TelnetThread::getLogin() const
{
    return t_login;
}
*/

/*
void TelnetThread::setPassword(const QString &password)
{
    t_password = password;
}
*/
/*
QString TelnetThread::getPassword() const
{
    return t_password;
}
*/
bool TelnetThread::isConnect()
{
    return t_isConnect;
}
void TelnetThread::free()
{
    if (--t_refCount == 0)
    {
        delete this;
    }
}
