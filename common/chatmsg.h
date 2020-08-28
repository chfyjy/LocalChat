#ifndef CHATMSG_H
#define CHATMSG_H

#include "ChatCtrl.h"
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QList>
#include <QMetaType>


const QString Msgid   = "msgid";
const QString Sendid  = "sendid";
const QString Recvid  = "recvid";
const QString Sendtime= "sendtime";
const QString Recvtime= "recvtime";
const QString Content = "content";
const QString Msgtype = "msgtype";
const QString Packnum = "packnum";
const QString Packseq = "packseq";

class ChatMsg
{
public:
    ChatMsg();
    QJsonDocument toJsonDocument();
    ChatMsg(const QJsonObject& jsonobj);
    ChatMsg(const QString& str);
    ChatMsg(const QString& _msgid, const QString& _sendid, const QString& _recvid,
               const QString& _sendtime, const QString& _recvtime, const QString& _content,
               MsgType _msgtype, int _packnum, int _packseq);
    bool isLastSub();
    QString msgid   ;//消息id
    QString sendid  ,//发送id
            recvid  ,//接收id
            sendtime,//发送时间
            recvtime,//接收时间
            content ;//消息内容
    MsgType msgtype ;//消息类型
    int     packnum , //消息分包数 大于1
            packseq ; //消息包序号 自1开始
};

#endif // CHATMSG_H
