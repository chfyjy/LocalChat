#include "workthread.h"

WorkThread::WorkThread(QObject *parent): QThread(parent)
{

}


void WorkThread::startThread()
{
    mutex.lock();
    stop = false;
    mutex.unlock();
    start();
}

void WorkThread::stopThread()
{
    mutex.lock();
    stop = true;
    mutex.unlock();
}
