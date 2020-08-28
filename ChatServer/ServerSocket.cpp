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
    //ChatMsg msg = ChatMsg(jsondoc.object());
    MessageHandling(ChatMsg(jsondoc.object()));
}

void ServerSocket::writeMsg(ChatMsg msg)
{
    write(msg.toJsonDocument().toJson());
    waitForBytesWritten();
    flush();
    qDebug() << msg.toJsonDocument().toJson();
}

bool ServerSocket::doRegister(ChatMsg msg)
{
    bool ok = false;
    int count = chatdb->getUserCount();
    QString account = fourNumberString(count+1);
    if(account == ServerID)
        msg.content = "注册失败,已不能注册新用户";
    else
    {
        if(chatdb->registerAccount(RegisterInfo(msg.content, account).toRegisterSQL()))
            msg.content ="注册成功,您的id是"+account+",请使用它和注册时的密码登录";
        else
            msg.content ="注册失败:"+chatdb->lastErrorString();
    }
    qDebug() << msg.content;
    msg.msgid = MsgID();
    msg.recvid = account;
    qDebug() << msg.recvid;
    msg.sendid = ServerID;
    userid = account;
    msg.ok = true;
    writeMsg(msg);
    return  ok;
}

void ServerSocket::MessageHandling(ChatMsg msg)
{
    switch (msg.msgtype)
    {
    case MsgType::REGISTER:doRegister(msg);break;
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
