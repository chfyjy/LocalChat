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
                 const QString& k1,const QString& k2);
    QString toRegisterStr();
    RegisterInfo(const QString& registerStr);
private:
    QString uname,
            pswd,
            key1,
            key2;
};

enum MsgType
{
    REGISTER,//注册
    FINDPSWD,//找回密码
    USERINFO,//用户信息修改
    TEXTMSG ,//文本消息
    FILEMSG ,//文件消息
    FRIENDA ,//添加好友
    FRIENDF ,//查找好友
    FRIENDD ,//删除好友
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
