#ifndef CHATTHREAD_H
#define CHATTHREAD_H

#include <QThread>
#include <QTcpSocket>

class ChatThread : public QThread
{
    Q_OBJECT
public:
    ChatThread(int socketDescriptor, QObject *parent);
    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);
private slots:
    void doReadyRead();
    void stopThread();

private:
    int socketDescriptor;
    QTcpSocket *socket;
};

#endif // CHATTHREAD_H
