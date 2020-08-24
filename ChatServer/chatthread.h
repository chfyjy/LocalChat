#ifndef CHATTHREAD_H
#define CHATTHREAD_H

#include "../common/workthread.h"
#include <QTcpSocket>

class ChatThread : public WorkThread
{
    Q_OBJECT
public:
    ChatThread(int socketDescriptor, QObject *parent);
    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    int port;
    QString ip;
};

#endif // CHATTHREAD_H
