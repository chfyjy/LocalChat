#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <logindialog.h>
#include <registerdialog.h>
#include <QTcpSocket>
#include "../common/chatmsg.h"
#include "../common/ChatCtrl.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void satrtRegister();
    void doRegister();
    void doReadyRead();
private:
    void initSocket();
    void writeMsg(ChatMsg msg);
private:
    Ui::Widget *ui;
    LoginDialog *loginDlg;
    RegisterDialog *registerDlg;
    QTcpSocket *socket;
};
#endif // WIDGET_H
