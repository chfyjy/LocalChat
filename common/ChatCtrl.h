#ifndef CHATCTRL_H
#define CHATCTRL_H

#include <QString>

const QString timeFmt = "yyyyMMDD hh:mm:ss";
const QString datetFmt = "yyyyMMDD";
const int ServerPort = 23456;
enum MsgType
{
    REGISTER,//注册
    FINDPSWD,//找回密码
    TEXTMSG,//文本消息
    FILEMSG,//文件消息
    ERRTYPE//错误的类型
};

#endif // CHATCTRL_H
