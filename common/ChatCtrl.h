#ifndef CHATCTRL_H
#define CHATCTRL_H

#include <QString>
#include <QTime>

const QString timeFmt = "yyyyMMdd hh:mm:ss";
const QString datetFmt = "yyyyMMdd";
const int ServerPort = 23456;
const QString UnregisteredID = "-10000";
const QString ServerID = "10000";
const QString SEPARATOR = "***";

class RegisterInfo
{
public:
    RegisterInfo(const QString& name, const QString& pwd,
                 const QString& k1,const QString& k2, const QString& uid=UnregisteredID);
    QString toRegisterStr();
    RegisterInfo(const QString& registerStr, const QString& uid=UnregisteredID);
    QString toRegisterSQL();
private:
    QString uname,
            userid,
            pswd,
            key1,
            key2;
};

class LoginInfo
{
public:
    QString userid;
    LoginInfo(const QString&uid, const QString& pwd);
    LoginInfo(const QString& loginStr);
    QString toLoginStr();
    QString toLoginSQL();
private:
    QString pswd;
};

class FindPSWDInfo
{
public:
    QString userid;
    QString key;
    FindPSWDInfo(const QString& uid, const QString& k);
    FindPSWDInfo(const QString& findRequestStr);
    QString toFindRequestStr();
    QString toCheckKeySQL();
    QString toQueryPswdSQL();
};

class UserInfo
{

};

enum MsgType
{
    REGISTER,//注册
    LOGIN,//登录
    FINDPSWD,//找回密码
    USERINF ,//用户信息
    USERINFC,//用户信息修改
    FRIENDA ,//添加好友
    FRIENDF ,//查找好友
    FRIENDD ,//删除好友
    TEXTMSG ,//消息(文本
    TEXTMSGG,//群消息(文本
    GROUPA  ,//加入群聊
    GROUPC  ,//创建群聊
    GROUPE  ,//退出群聊
    GROUPF  ,//查找群聊
    ERRTYPE ,//错误的类型
};

QString MsgID();
QString Send_RecvTime();
QString fourNumberString(int);


#endif // CHATCTRL_H
