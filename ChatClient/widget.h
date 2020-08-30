#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>

#include <logindialog.h>
#include <registerdialog.h>
#include <findpswddlg.h>
#include <userinfodlg.h>

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
    void startFindPswd();
    void doFindPswd();
    void doRegister();
    void doLogin();
    void receiveMessage();
    void putUserInfo();
    void on_ChangeInfoPBtn_clicked();

private:
    void initSocket();
    void writeMsg(ChatMsg msg);

    void MessageHandling(ChatMsg msg);
    void registerHandle(ChatMsg msg);
    void loginHandle(ChatMsg msg);
    void findPswdHandle(ChatMsg msg);
    void userInfoGetHandle(ChatMsg msg);
    void userInfoPutHandle(ChatMsg msg);
private:
    Ui::Widget *ui;
    FindPswdDlg *findpswdDlg;
    LoginDialog *loginDlg;
    RegisterDialog *registerDlg;
    UserInfoDlg *userinfoDlg;
    QTcpSocket *socket;
    QString userid;
};
#endif // WIDGET_H
