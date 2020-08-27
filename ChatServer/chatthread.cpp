#include "chatthread.h"
#include <QDebug>
#include <QHostAddress>

ChatThread::ChatThread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
    start();
}

void ChatThread::doReadyRead()
{
    qDebug() << socket->readAll();
}

void ChatThread::stopThread()
{
    quit();
    qDebug() <<"quit";
    wait();
    qDebug() <<"wait";
}

void ChatThread::run()
{
    socket = new QTcpSocket(nullptr);
    socket->setSocketDescriptor(socketDescriptor);
    qDebug() << connect(socket, &QIODevice::readyRead, this, &ChatThread::doReadyRead, Qt::ConnectionType::QueuedConnection);
    qDebug() << connect(socket,&QTcpSocket::disconnected, this, &ChatThread::stopThread, Qt::ConnectionType::QueuedConnection);
    socket->write("test");
    exec();
}
