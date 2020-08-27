#ifndef CHATDATEBASE_H
#define CHATDATEBASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
const QString userCountSql = "SELECT COUNT(userid) FROM userLogin";
const QString groupCountSql = "SELECT COUNT(DISTINCT groupid) FROM chatgroup";
class ChatDataBase : public QObject
{
    Q_OBJECT
public:
    explicit ChatDataBase(QObject *parent = nullptr);
    ~ChatDataBase();
    bool IsOpen();
    bool createTables();
    QString lastErrorString();
    int getUserCount();
    int getGroupCount();
    int getCount(const QString& countQuerySql);


signals:

private:
    QSqlDatabase chatDB;
    QString errString;
    bool opened;
};

#endif // CHATDATEBASE_H