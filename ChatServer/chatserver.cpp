#include "chatserver.h"
#include <QDebug>

ChatServer::ChatServer(QObject *parent): QTcpServer(parent)
{
    setMaxPendingConnections(1000);//最大连接数设为1000
}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "incomingConnection";
    ChatThread *thread = new ChatThread(socketDescriptor, nullptr);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
