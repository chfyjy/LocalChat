#ifndef CHATTHREAD_H
#define CHATTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <../common/chatmsg.h>
#include <chatdatabase.h>

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
    void doReadyRead();
    void stopThread();

private:
    void MessageHandling(ChatMsg msg, int index);
    void MessageHandling(const QString& msgid);
    void MessageReorganization(subChatMsg submsg);
    int Msgat(const QString& msgid);
private:
    int socketDescriptor;
    QTcpSocket *socket;
    QList<ChatMsg> msglist;
    ChatDataBase *chatdb;
};

#endif // CHATTHREAD_H
