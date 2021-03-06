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
    switch (length)
    {
    case 1: return "0";
    case 2: return "00";
    case 3: return "000";
    }
    return "";
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
             const QString& k1,const QString& k2, const QString& uid)
    :uname(name), pswd(pwd), key1(k1), key2(k2), userid(uid){}

QString RegisterInfo::toRegisterStr()
{
    return uname+ SEPARATOR+pswd+SEPARATOR+key1+SEPARATOR+key2+SEPARATOR;
}

RegisterInfo::RegisterInfo(const QString& registerStr, const QString& uid)
{
    QStringList strlist = registerStr.split(SEPARATOR);
    uname = strlist[0];
    pswd = strlist[1];
    key1 = strlist[2];
    key2 = strlist[3];
    userid = uid;
}

QString RegisterInfo::toRegisterSQL()
{
    return  QString("insert into userLogin "
            "(userid, nickName, userpswd, pswdkey1, pswdkey2) "
            "values('%1','%2','%3','%4','%5')")
            .arg(userid).arg(uname).arg(pswd).arg(key1).arg(key2);
}

LoginInfo::LoginInfo(const QString&uid, const QString& pwd)
           :userid(uid), pswd(pwd){}

LoginInfo::LoginInfo(const QString& loginStr)
{
    QStringList strlist = loginStr.split(SEPARATOR);
    userid = strlist[0];
    pswd = strlist[1];
}

QString LoginInfo::toLoginStr()
{
    return  userid+SEPARATOR+pswd+SEPARATOR;
}

QString LoginInfo::toLoginSQL()
{
    return QString("select count(userid) from userLogin "
                   "where userid='%1' and userpswd='%2'")
            .arg(userid).arg(pswd);
}

FindPSWDInfo::FindPSWDInfo(const QString& uid, const QString& k)
              :userid(uid), key(k){}

FindPSWDInfo::FindPSWDInfo(const QString& findRequestStr)
{
    QStringList strlist = findRequestStr.split(SEPARATOR);
    userid = strlist[0];
    key = strlist[1];
}

QString FindPSWDInfo::toFindRequestStr()
{
    return  userid+SEPARATOR+key+SEPARATOR;
}

QString FindPSWDInfo::toCheckKeySQL()
{
    return QString("select count(userid) from userLogin "
                   "where userid='%1' and (pswdkey1='%2' or pswdkey2 = '%3')")
            .arg(userid).arg(key).arg(key);
}

QString FindPSWDInfo::toQueryPswdSQL()
{
    return QString("select userpswd from userLogin where userid='%1'").arg(userid);
}



UserInfo::UserInfo(const QString& uid):userid(uid)
{
    inited = false;
}

UserInfo::UserInfo(const QString& uid, const QString&addr, const QString& birth, const QString&pnum, bool g, int a)
:userid(uid),address(addr),birthday(birth),phonenum(pnum), gender(g), age(a)
{
    inited = true;
}

UserInfo::UserInfo(const QString& uid, const QString& userInfoStr)
    :userid(uid)
{
    QStringList strlist = userInfoStr.split(SEPARATOR);
    if(strlist[0] == "1")
        gender = true;
    else
        gender = false;
    age = strlist[1].toInt();
    birthday = strlist[2];
    address = strlist[3];
    phonenum = strlist[4];
    inited = true;
}
QString UserInfo::toQueryInfoSql()
{
    return QString("select gender, age, birthday, address, phonenumber from userInfo where uid='%1'").arg(userid);
}
/*
                "(uid varchar(5) references userLogin(userid),"//账号
                "gender bool,"//性别 true 男 false 女
                "age int,"//年龄
                "birthday varchar(8),"//生日
                "address varchar(50),"//地址
                "phonenumber varchar(20)"//手机号/电话号
*/
QString UserInfo::toReplaceInfoSql()
{
    return  QString("replace into userInfo values('%1',%2,%3,'%4','%5','%6');")
            .arg(userid).arg(gender).arg(age).arg(birthday).arg(address).arg(phonenum);
}

QString UserInfo::toQueryInfoHasSql()
{
    return QString("select count(age) from userInfo where uid='%1'").arg(userid);
}

QString UserInfo::userInfoStr()
{
    return QString("%1%2%3%4%5%6%7%8%9%10")
            .arg(gender).arg(SEPARATOR).arg(age).arg(SEPARATOR)
            .arg(birthday).arg(SEPARATOR).arg(address).arg(SEPARATOR)
            .arg(phonenum).arg(SEPARATOR);
}


