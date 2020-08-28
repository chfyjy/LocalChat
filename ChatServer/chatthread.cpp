#include "chatthread.h"
#include <QDebug>
#include <QHostAddress>

ChatThread::ChatThread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
    start();
}


void ChatThread::stopThread()
{
    quit();
    wait();
}

void ChatThread::run()
{
    socket = new ServerSocket(nullptr);
    socket->setSocketDescriptor(socketDescriptor);
    qDebug() << connect(socket,&QTcpSocket::disconnected, this, &ChatThread::stopThread, Qt::ConnectionType::QueuedConnection);
    socket->write("test");
    exec();
}
