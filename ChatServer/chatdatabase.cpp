#include "chatdatabase.h"
#include <QVariant>

ChatDataBase::ChatDataBase(QObject *parent) : QObject(parent)
{
    chatDB = QSqlDatabase::addDatabase("QSQLITE");
    chatDB.setHostName("chatDB");
    chatDB.setDatabaseName("chatDB.db");
    chatDB.setUserName("chatDB");
    chatDB.setPassword("chatDB");
    opened = chatDB.open();
}

ChatDataBase::~ChatDataBase()
{
    chatDB.close();
    opened = false;
}

bool ChatDataBase::IsOpen()
{
    return  opened;
}

QString ChatDataBase::lastErrorString()
{
    return errString;
}

bool ChatDataBase::createTables()
{
    QSqlQuery query(chatDB);
    query.exec("create table if not exists userLogin("//用户登陆信息表
               "userid varchar(4) primary key,"//账号
               " nickName varchar(50)," //昵称
               " userpswd varchar(10),"//密码
               " pswdkey1 varchar(20),"//密保1
               " pswdkey2 varchar(20),"//密保2
               " bool online,"//是否在线
               " logintime varchar(17),"//登录时间
               " logouttime varchar(17)"//登出时间
               ")");
    if(query.lastError().type() != QSqlError::ErrorType::NoError)
    {
        errString = query.lastError().text();
        return false;
    }
    query.exec("create table if not exists userInfo"//用户信息表
               "(uid varchar(5) references userLogin(userid),"//账号
               "gender bool,"//性别
               "age int,"//年龄
               "birthday varchar(8),"//生日
               "address varchar(50),"//地址
               "phonenumber varchar(20)"//手机号/电话号
               ")");
    if(query.lastError().type() != QSqlError::ErrorType::NoError)
    {
        errString = query.lastError().text();
        return false;
    }
    query.exec("create table if not exists chatgroup("
               "groupid varchar(5),"//群号
               "description varchar(15),"//群描述
               "memberid varchar(5),"//群成员
               "memberpermission int"//0 群主 1 群管理 2 群员
               ")");
    query.exec("create table if not exists offlineMessage("//离线消息表 转发失败或因为接收方离线无法转发的消息暂存表 转发后删除
               "msgid varchar(30) primary key," //消息id
               "sendid varchar(5),"//发送id
               "recvid varchar(5),"//接收id
               "sendtime varchar(17),"//发送时间
               "recvtime varchar(17),"//接收时间
               "msgtype int,"//消息类型
               "packnum int,"//消息分包数 大于1
               "packseq int,"//消息序号 自1开始
               "content varchar(10240)"//消息内容 长度限制10240000
               ")");
    return true;
}

int ChatDataBase::getCount(const QString& countQuerySql)
{
    QSqlQuery query(chatDB);
    query.exec(countQuerySql);
    if(query.lastError().type() != QSqlError::ErrorType::NoError)
    {
        errString = query.lastError().text();
        return -1;
    }
    while (query.next()) {
             return query.value(0).toInt();
         }
    return -1;
}

int ChatDataBase::getUserCount()
{
    return getCount(userCountSql);
}

int ChatDataBase::getGroupCount()
{
    return getCount(groupCountSql);
}
