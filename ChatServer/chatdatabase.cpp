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

void ChatDataBase::close()
{
    chatDB.close();
}

bool ChatDataBase::IsOpen()
{
    return  opened;
}

QString ChatDataBase::lastErrorString()
{
    return errString;
}

bool ChatDataBase::execSQL(const QString& sqlstr)
{
    QSqlQuery query(chatDB);
    query.exec(sqlstr);
    if(query.lastError().type() != QSqlError::ErrorType::NoError)
    {
        errString = query.lastError().text();
        return false;
    }
    return true;
}

bool ChatDataBase::execSQL(const QString& querySql, QVariant* result)
{
    QSqlQuery query(chatDB);
    query.exec(querySql);
    if(query.lastError().type() != QSqlError::ErrorType::NoError)
    {
        errString = query.lastError().text();
        return false;
    }
    while (query.next())
             *result = query.value(0);
    return true;

}

QString ChatDataBase::getPswd(const QString& queryPswdSql)
{
    QString pswd = "";
    QVariant result;
    execSQL(queryPswdSql, &result);
    pswd = result.toString();
    return  pswd;
}

bool ChatDataBase::createTables()
{
    QSqlQuery query(chatDB);
    if(!execSQL("create table if not exists userLogin("//用户登陆信息表
               "userid varchar(4) primary key,"//账号
               " nickName varchar(50)," //昵称
               " userpswd varchar(10),"//密码
               " pswdkey1 varchar(20),"//密保1
               " pswdkey2 varchar(20),"//密保2
               " bool online,"//是否在线
               " logintime varchar(17),"//登录时间
               " logouttime varchar(17)"//登出时间
               ")"))
        return false;
    if(!execSQL("create table if not exists userInfo"//用户信息表
                "(uid varchar(5) references userLogin(userid),"//账号
                "gender bool,"//性别 true 男 false 女
                "age int,"//年龄
                "birthday varchar(8),"//生日
                "address varchar(50),"//地址
                "phonenumber varchar(20)"//手机号/电话号
                ")"))
        return false;
    if(!execSQL("create table if not exists chatgroup("
                "groupid varchar(5),"//群号
                "description varchar(15),"//群描述
                "memberid varchar(5),"//群成员
                "memberpermission int"//0 群主 1 群管理 2 群员
                ")"))
        return false;
    if(!execSQL("create table if not exists offlineMessage("//离线消息表 转发失败或因为接收方离线无法转发的消息暂存表 转发后删除
               "msgid varchar(30) primary key," //消息id
               "sendid varchar(5),"//发送id
               "recvid varchar(5),"//接收id
               "sendtime varchar(17),"//发送时间
               "recvtime varchar(17),"//接收时间
               "msgtype int,"//消息类型
               "packnum int,"//消息分包数 大于1
               "packseq int,"//消息序号 自1开始
               "content varchar(10240)"//消息内容 长度限制10240000
               ")"))
        return false;
    return true;
}
UserInfo ChatDataBase::getUserInfo(const QString& sql)
{
    UserInfo ret = UserInfo("");
    QSqlQuery query(chatDB);
    query.exec(sql);
    if(query.lastError().type() != QSqlError::ErrorType::NoError)
        errString = query.lastError().text();
    else
    {
        while (query.next())
        {
            ret.gender =  query.value(0).toBool();
            ret.age = query.value(1).toInt();
            ret.birthday = query.value(2).toString();
            ret.address = query.value(3).toString();
            ret.phonenum = query.value(4).toString();
        }
    }
    return ret;
}
bool ChatDataBase::registerAccount(const QString& registerSQL)
{
    return execSQL(registerSQL);
}

int ChatDataBase::getCount(const QString& countQuerySql)
{
    int count = -1;
    QVariant result;
    execSQL(countQuerySql, &result);
    count = result.toInt();
    return count;
}

int ChatDataBase::getUserCount()
{
    return getCount(userCountSql);
}

int ChatDataBase::getGroupCount()
{
    return getCount(groupCountSql);
}
