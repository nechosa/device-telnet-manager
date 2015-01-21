#ifndef TELNETTHREAD_H
#define TELNETTHREAD_H

#include <QThread>
#include <QMutex>


class TelnetThread : public QThread
{
    Q_OBJECT



public:
    static TelnetThread* getInstance();

    void run();
    void transaction(const QByteArray& request, int waitTimeout);
    void connectTelnet

    static TelnetThread();

private:

    static TelnetThread* t_instance;
    static int t_refCount;

};

#endif // TELNETTHREAD_H
