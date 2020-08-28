#include "chatmsg.h"

ChatMsg::ChatMsg()
{
    msgid   ="";
    sendid  ="";
    recvid  ="";
    sendtime="";
    recvtime="";
    content ="";
    msgtype =ERRTYPE;
    packnum =0;
    packseq =0;
    ok = false;
}

QJsonDocument ChatMsg::toJsonDocument()
{
    QJsonObject jsonobj;
    jsonobj.insert(Msgid   ,QJsonValue(msgid   ));
    jsonobj.insert(Sendid  ,QJsonValue(sendid  ));
    jsonobj.insert(Recvid  ,QJsonValue(recvid  ));
    jsonobj.insert(Sendtime,QJsonValue(sendtime));
    jsonobj.insert(Recvtime,QJsonValue(recvtime));
    jsonobj.insert(Content ,QJsonValue(content ));
    jsonobj.insert(Msgtype ,QJsonValue((int)msgtype ));
    jsonobj.insert(Packnum ,QJsonValue(packnum ));
    jsonobj.insert(Packseq ,QJsonValue(packseq ));
    jsonobj.insert(okstr, QJsonValue(ok));

    return QJsonDocument(jsonobj);
}

ChatMsg::ChatMsg(const QJsonObject& jsonobj)
{
    msgid    = jsonobj.value(Msgid   ).toString();
    sendid   = jsonobj.value(Sendid  ).toString();
    recvid   = jsonobj.value(Recvid  ).toString();
    sendtime = jsonobj.value(Sendtime).toString();
    recvtime = jsonobj.value(Recvtime).toString();
    content  = jsonobj.value(Content ).toString();
    msgtype  = (MsgType)jsonobj.value(Msgtype ).toInt();
    packnum  = jsonobj.value(Packnum ).toInt();
    packseq  = jsonobj.value(Packseq ).toInt();
    ok = jsonobj.value(okstr).toBool();
}

bool ChatMsg::isLastSub()
{
    return  (packnum == packseq);
}

ChatMsg::ChatMsg(const QString& _msgid, const QString& _sendid, const QString& _recvid,
           const QString& _sendtime, const QString& _recvtime, const QString& _content,
           MsgType _msgtype, int _packnum, int _packseq):
    msgid(_msgid),sendid(_sendid),recvid(_recvid),
    sendtime(_sendtime),recvtime(_recvtime),content(_content),
    msgtype(_msgtype),packnum(_packnum),packseq(_packseq)
{

}
