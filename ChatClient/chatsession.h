#ifndef CHATSESSION_H
#define CHATSESSION_H

#include "../common/workthread.h"
#include <QTcpSocket>

class ChatSession : public WorkThread
{
    Q_OBJECT
public:
    explicit ChatSession(QObject *parent = nullptr);

protected:
    void run() override;

signals:
private slots:
    void doReadyRead();

private:

    QTcpSocket *socket;
};

#endif // CHATSESSION_H
