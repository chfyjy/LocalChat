#include "ChatCtrl.h"
#include <QDateTime>

int randomNumber(void)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    return qrand()%9;
}
QString MsgID(QString uid)
{
    return uid + QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch());
}

QString Send_RecvTime()
{
    return QDateTime::currentDateTime().toString(timeFmt);
}
