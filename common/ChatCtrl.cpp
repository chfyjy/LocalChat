#include "ChatCtrl.h"
#include <QDateTime>

int randomNumber(void)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    return qrand()%9;
}
QString MsgID()
{
    return QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch());
}

QString Send_RecvTime()
{
    return QDateTime::currentDateTime().toString(timeFmt);
}

QString zeroString(int length)
{
    switch (length) {
    case 1: return "0";
    case 2: return "00";
    case 3: return "000";
    }
}

QString fourNumberString(int num)
{
    QString numstr = QString::number(num);
    if(numstr.length() < 4)
    {
        int addlen = 4 - numstr.length();
        numstr = zeroString(addlen) + numstr;
    }
    return  numstr;
}

RegisterInfo::RegisterInfo(const QString& name, const QString& pwd,
             const QString& k1,const QString& k2)
    :uname(name), pswd(pwd), key1(k1), key2(k2)
{

}

QString RegisterInfo::toRegisterStr()
{
    return uname+ SEPARATOR+pswd+SEPARATOR+key1+SEPARATOR+key2+SEPARATOR;
}

RegisterInfo::RegisterInfo(const QString& registerStr)
{
    QStringList strlist = registerStr.split(SEPARATOR);
    uname = strlist[0];
    pswd = strlist[1];
    key1 = strlist[2];
    key2 = strlist[3];
}
