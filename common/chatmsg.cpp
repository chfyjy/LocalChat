#include "chatmsg.h"

subChatMsg::subChatMsg()
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
}

QJsonObject subChatMsg::toJsonObject()
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

    return QJsonObject(jsonobj);
}

subChatMsg::subChatMsg(const QJsonObject& jsonobj)
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
}

subChatMsg::subChatMsg(const QString& _msgid, const QString& _sendid, const QString& _recvid,
           const QString& _sendtime, const QString& _recvtime, const QString& _content,
           MsgType _msgtype, int _packnum, int _packseq):
    msgid(_msgid),sendid(_sendid),recvid(_recvid),
    sendtime(_sendtime),recvtime(_recvtime),content(_content),
    msgtype(_msgtype),packnum(_packnum),packseq(_packseq)
{

}

QString initRegisterContent(const QString& name, const QString& pswd,
                            const QString& key1, const QString&key2)
{
    return name+ SEPARATOR+pswd+SEPARATOR+key1+SEPARATOR+key2+SEPARATOR;
}

ChatMsg::ChatMsg(const subChatMsg& scmsg)
{
    subpacks.clear();
    subpacks << scmsg;
}

ChatMsg::ChatMsg(const QList<subChatMsg>& scmsgs)
{
    subpacks = scmsgs;
}

void ChatMsg::addSubChatMsg(const subChatMsg& scmsg)
{
    subpacks << scmsg;
}

QList<QJsonDocument> ChatMsg::toJsonDocument()
{
    int count = subpacks.count();
    if(count < 1)
        return  QList<QJsonDocument>();
    QList<QJsonDocument> doclist;
    for(int i = 0; i < count; i++)
        doclist.append(QJsonDocument(subpacks[i].toJsonObject()));
    return doclist;
}
