#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>

class WorkThread : public QThread
{
    Q_OBJECT
public:
    WorkThread(QObject *parent = nullptr);
    void startThread();
    void stopThread();
    
    bool stop;
    QMutex mutex;
};

#endif // WORKTHREAD_H
