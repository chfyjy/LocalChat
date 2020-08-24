#include "chatthread.h"
#include <QDebug>
#include <QHostAddress>

ChatThread::ChatThread(int socketDescriptor, QObject *parent)
    : WorkThread(parent), socketDescriptor(socketDescriptor)
{
    startThread();
}

void ChatThread::run()
{
    QTcpSocket socket;
    socket.setSocketDescriptor(socketDescriptor);
    qDebug() << socket.peerPort();
    qDebug() << socket.peerAddress().toString();
    int tmp = socket.write("test\n");
    qDebug() << tmp;
    while(!stop)
    {
    }
    socket.close();
}
