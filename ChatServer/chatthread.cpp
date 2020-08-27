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
    QJsonParseError error;
    QJsonDocument jsondoc = QJsonDocument::fromJson(socket->readAll(), &error);
    subChatMsg submsg = subChatMsg(jsondoc.object());
    MessageReorganization(submsg);
}

int ChatThread::Msgat(const QString& msgid)
{
    int count = msglist.count();
    for(int i = 0; i < count; i++)
    {
        if(msgid == msglist[i].msgid)
            return i;
    }
    return -1;
}

void ChatThread::MessageReorganization(subChatMsg submsg)
{
    int count = msglist.count();
    if(count < 1)
        msglist.append(ChatMsg(submsg));
    else
    {
        int index = Msgat(submsg.msgid);
        if(index == -1)
            msglist.append(ChatMsg(submsg));
        else
            msglist[index].addSubChatMsg(submsg);
    }
    if(submsg.isLastSub())
        MessageHandling(submsg.msgid);
}

void ChatThread::MessageHandling(ChatMsg msg, int index)
{
    switch (msg.msgtype)
    {
    case MsgType::REGISTER:
    {
        int count = chatdb->getUserCount();
        QString account = fourNumberString(count+1);
        if(account == ServerID)
            msg.setSubContent("注册失败,用户过多已不能注册新用户", 0);
        else
            msg.setSubContent("注册成功,您的id是"+account+",请使用它和注册时的密码登录",0);
        msg.msgid = MsgID();
        msg.recvid = account;
        userid = account;
    }
        break;
    case MsgType::FINDPSWD:break;
    case MsgType::USERINFO:break;
    case MsgType::TEXTMSG :break;
    case MsgType::FILEMSG :break;
    case MsgType::FRIENDA :break;
    case MsgType::FRIENDF :break;
    case MsgType::FRIENDD :break;
    case MsgType::GROUPA  :break;
    case MsgType::GROUPC  :break;
    case MsgType::GROUPE  :break;
    case MsgType::GROUPF  :break;
    case MsgType::ERRTYPE :break;
    }
}

void ChatThread::MessageHandling(const QString& msgid)
{
    int count = msglist.count();
    if(count < 1)
        return;
    int index = Msgat(msgid);
    MessageHandling(msglist[index], index);
}

void ChatThread::stopThread()
{
    quit();
    wait();
    chatdb->close();
}

void ChatThread::run()
{
    chatdb = new ChatDataBase();
    socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);
    qDebug() << connect(socket, &QIODevice::readyRead, this, &ChatThread::doReadyRead, Qt::ConnectionType::QueuedConnection);
    qDebug() << connect(socket,&QTcpSocket::disconnected, this, &ChatThread::stopThread, Qt::ConnectionType::QueuedConnection);
    socket->write("test");
    exec();
}
