#ifndef CHATDATEBASE_H
#define CHATDATEBASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

class ChatDataBase : public QObject
{
    Q_OBJECT
public:
    explicit ChatDataBase(QObject *parent = nullptr);
    ~ChatDataBase();
    bool IsOpen();
    bool createTables();
    QString lastErrorString();

signals:

private:
    QSqlDatabase chatDB;
    QString errString;
    bool opened;

};

#endif // CHATDATEBASE_H
