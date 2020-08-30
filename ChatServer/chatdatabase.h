#ifndef CHATDATEBASE_H
#define CHATDATEBASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include "../common/ChatCtrl.h"

const QString userCountSql = "SELECT COUNT(userid) FROM userLogin";
const QString groupCountSql = "SELECT COUNT(DISTINCT groupid) FROM chatgroup";

class ChatDataBase : public QObject
{
    Q_OBJECT
public:
    explicit ChatDataBase(QObject *parent = nullptr);
    ~ChatDataBase();
    bool IsOpen();
    void close();
    bool createTables();
    QString lastErrorString();
    int getCount(const QString& countQuerySql);
    int getUserCount();
    int getGroupCount();
    bool registerAccount(const QString& sql);
    QString getPswd(const QString& sql);
    UserInfo getUserInfo(const QString& sql);
    bool execSQL(const QString&);
    bool execSQL(const QString&, QVariant* result);

signals:
private:

private:
    QSqlDatabase chatDB;
    QString errString;
    bool opened;
};

#endif // CHATDATEBASE_H
