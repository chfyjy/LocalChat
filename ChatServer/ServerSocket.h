#ifndef CHATSOCKET_H
#define CHATSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <chatdatabase.h>
#include <../common/chatmsg.h>

class ServerSocket : public QTcpSocket
{
    Q_OBJECT
public:
    QString userid;
    ServerSocket(QObject *parent = nullptr);
    ~ServerSocket();
private slots:
    void receiveMessage();
private:
    void MessageHandling(ChatMsg msg);

    void doRegister(ChatMsg);
    void doLogin(ChatMsg);

    int Msgat(const QString& msgid);
    void writeMsg(ChatMsg msg);
private:
    ChatDataBase *chatdb;
};

#endif // CHATSOCKET_H
