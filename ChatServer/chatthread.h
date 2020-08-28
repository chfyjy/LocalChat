#ifndef CHATTHREAD_H
#define CHATTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <chatdatabase.h>
#include <ServerSocket.h>

class ChatThread : public QThread
{
    Q_OBJECT
public:
    QString userid;
    ChatThread(int socketDescriptor, QObject *parent);
    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);
private slots:
    void stopThread();

private:
    int socketDescriptor;
    ServerSocket *socket;
};

#endif // CHATTHREAD_H
