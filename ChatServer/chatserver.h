#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QTcpServer>
#include <chatthread.h>

class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    ChatServer(QObject *parent = 0);
protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // CHATSERVER_H
