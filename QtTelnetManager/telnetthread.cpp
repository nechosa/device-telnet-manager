#include "telnetthread.h"

TelnetThread::TelnetThread()
{
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
