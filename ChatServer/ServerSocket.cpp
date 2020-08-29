#include "ServerSocket.h"

ServerSocket::ServerSocket(QObject *parent):
    QTcpSocket(parent)
{
    chatdb = new ChatDataBase();
    connect(this, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}


ServerSocket::~ServerSocket()
{
    chatdb->close();
}

void ServerSocket::receiveMessage()
{
    QJsonParseError error;
    QJsonDocument jsondoc = QJsonDocument::fromJson(readAll(), &error);
    MessageHandling(ChatMsg(jsondoc.object()));
}

void ServerSocket::writeMsg(ChatMsg msg)
{
    write(msg.toJsonDocument().toJson());
    waitForBytesWritten();
    flush();
    qDebug() << msg.toJsonDocument().toJson();
}

void ServerSocket::doRegister(ChatMsg msg)
{
    int count = chatdb->getUserCount();
    QString account = fourNumberString(count+1);
    if(account == ServerID)
    {
        msg.content = "注册失败,已不能注册新用户";
        msg.ok = false;
    }
    else
    {
        if(chatdb->registerAccount(RegisterInfo(msg.content, account).toRegisterSQL()))
        {
            msg.ok = true;
            msg.content ="注册成功,您的id是"+account+",请使用它和注册时的密码登录";
        }
        else
        {
            msg.ok = false;
            msg.content ="注册失败:"+chatdb->lastErrorString();
        }
    }
    qDebug() << msg.content;
    msg.msgid = MsgID();
    msg.recvid = UnregisteredID;
    qDebug() << msg.recvid;
    msg.sendid = ServerID;
    writeMsg(msg);
}

void ServerSocket::doLogin(ChatMsg msg)
{
    LoginInfo logininfo = LoginInfo(msg.content);
    int has = chatdb->getCount(logininfo.toLoginSQL());
    if(has == 1)
    {
        msg.ok = true;
        msg.content="登录成功";
    }
    else
    {
        msg.ok = false;
        msg.content = "用户不存在/密码错误，请重试";
    }
    qDebug() << msg.content;
    msg.msgid = MsgID();
    msg.recvid = logininfo.userid;
    qDebug() << msg.recvid;
    msg.sendid = ServerID;
    writeMsg(msg);
}

void ServerSocket::doFindPswd(ChatMsg msg)
{
    FindPSWDInfo findinfo = FindPSWDInfo(msg.content);
    int has = chatdb->getCount(findinfo.toCheckKeySQL());
    if(has == 1)
    {
        msg.ok = true;
        msg.content = "你的密码是" + chatdb->getPswd(findinfo.toQueryPswdSQL());
    }
    else
    {
        msg.ok = false;
        msg.content = "用户不存在/密保错误，请重试";
    }
    qDebug() << msg.content;
    msg.msgid = MsgID();
    msg.recvid = UnregisteredID;
    qDebug() << msg.recvid;
    msg.sendid = ServerID;
    writeMsg(msg);
}

void ServerSocket::MessageHandling(ChatMsg msg)
{
    switch (msg.msgtype)
    {
    case MsgType::REGISTER:doRegister(msg);break;
    case MsgType::LOGIN   :doLogin(msg);break;
    case MsgType::FINDPSWD:doFindPswd(msg);break;
    case MsgType::USERINFG:break;
    case MsgType::USERINFP:break;
    case MsgType::FRIENDA :break;
    case MsgType::FRIENDF :break;
    case MsgType::FRIENDD :break;
    case MsgType::TEXTMSG :break;
    case MsgType::TEXTMSGG:break;
    case MsgType::GROUPA  :break;
    case MsgType::GROUPC  :break;
    case MsgType::GROUPE  :break;
    case MsgType::GROUPF  :break;
    case MsgType::ERRTYPE :break;
    }
}
