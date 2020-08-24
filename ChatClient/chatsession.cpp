#include "chatsession.h"
#include "../common/ChatCtrl.h"
#include <QDebug>

ChatSession::ChatSession(QObject *parent)
    : WorkThread(parent)
{

}


void ChatSession::doReadyRead()
{
    qDebug() << socket->readAll();
}

void ChatSession::run()
{
    socket = new QTcpSocket(nullptr);
    connect(socket, &QIODevice::readyRead, this, &ChatSession::doReadyRead);
    socket->connectToHost("127.0.0.1", ServerPort, QIODevice::ReadWrite, QAbstractSocket::IPv4Protocol);
    qDebug() << socket->waitForConnected();
    while(!stop)
    {
    }
    socket->close();
    socket->deleteLater();
}
