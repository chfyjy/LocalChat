#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    showGroupOption(false);
    showFriendOption(false);
    initSocket();
    loginDlg = new LoginDialog(this);
    qDebug() << connect(loginDlg, &LoginDialog::needRegister, this, &Widget::satrtRegister);
    qDebug() << connect(loginDlg, &LoginDialog::needLogin, this, &Widget::doLogin);
    qDebug() << connect(loginDlg, &LoginDialog::needFindPswd, this, &Widget::startFindPswd);
    if(loginDlg->exec()!=QDialog::Accepted)
        exit(0);
}

Widget::~Widget()
{
    if(socket)
    {
        socket->disconnectFromHost();
        socket->deleteLater();
    }
    delete ui;
}

void Widget::receiveMessage()
{
    QJsonParseError error;
    QJsonDocument jsondoc = QJsonDocument::fromJson(socket->readAll(), &error);
    ChatMsg msg = ChatMsg(jsondoc.object());
    qDebug() << msg.content;
    MessageHandling(msg);
}

void Widget::registerHandle(ChatMsg msg)
{
    registerDlg->deleteLater();
    if(!msg.ok)
        return;
    QMessageBox::information(this, "register", msg.content);
    loginDlg->doRegisterDone();
}

void Widget::loginHandle(ChatMsg msg)
{
    if(msg.ok)
    {
        qDebug() << msg.content;
        loginDlg->accept();
        loginDlg->deleteLater();
        userid = msg.recvid;
        ui->UIDlabel->setText(userid);
    }
    else
        QMessageBox::information(this, "login", msg.content);
}

void Widget::findPswdHandle(ChatMsg msg)
{
    findpswdDlg->deleteLater();
    QMessageBox::information(this, "find the password", msg.content);
}

void Widget::userInfoGetHandle(ChatMsg msg)
{
    qDebug() << "userInfoGetHandle";
    if(!msg.ok)
    {
        QMessageBox::information(this, "User information get", "信息获取失败");
        return;
    }
    if(msg.content == "" )
        userinfoDlg = new UserInfoDlg(this);
    else
        userinfoDlg = new UserInfoDlg(UserInfo(msg.recvid, msg.content), this);
    connect(userinfoDlg, &UserInfoDlg::needPutUserInfo, this, &Widget::putUserInfo);
    userinfoDlg->exec();
}

void Widget::putUserInfo()
{
    QString content=userinfoDlg->uinfo.userInfoStr();
    ChatMsg userinfoPutMsg = ChatMsg(MsgID(), userid, ServerID, Send_RecvTime(), "", content, MsgType::USERINFP, 1, 1);
    userinfoPutMsg.ok = false;
    writeMsg(userinfoPutMsg);
}

void Widget::userInfoPutHandle(ChatMsg msg)
{
    qDebug() << "userInfoPutHandle" << msg.msgtype << msg.content;
    QMessageBox::information(userinfoDlg, "user info", msg.content);
}

void Widget::MessageHandling(ChatMsg msg)
{
    switch (msg.msgtype)
    {
    case MsgType::REGISTER:registerHandle(msg);break;
    case MsgType::LOGIN   :loginHandle(msg);break;
    case MsgType::FINDPSWD:findPswdHandle(msg);break;
    case MsgType::USERINFG:userInfoGetHandle(msg);break;
    case MsgType::USERINFP:userInfoPutHandle(msg);break;
    case MsgType::FRIENDA :break;
    case MsgType::FRIENDF :break;
    case MsgType::FRIENDD :break;
    case MsgType::TEXTMSG :break;
    case MsgType::TEXTMSGG:break;
    case MsgType::GROUPA  :break;
    case MsgType::GROUPC  :break;
    case MsgType::GROUPE  :break;
    case MsgType::GROUPF  :break;
    case MsgType::ERRTYPE :break;
    }
}

void Widget::writeMsg(ChatMsg msg)
{
    qDebug() << msg.toJsonDocument().toJson();
    socket->write(msg.toJsonDocument().toJson());
}

void Widget::initSocket()
{
    socket = new QTcpSocket(nullptr);
    qDebug() << connect(socket, &QIODevice::readyRead, this, &Widget::receiveMessage, Qt::ConnectionType::AutoConnection);
    socket->connectToHost("127.0.0.1", ServerPort, QIODevice::ReadWrite, QAbstractSocket::IPv4Protocol);
    qDebug() << socket->waitForConnected();
}

void Widget::doRegister()
{
    QString content = RegisterInfo(registerDlg->nickname, registerDlg->pswd, registerDlg->key1, registerDlg->key2).toRegisterStr();
    ChatMsg registerMsg = ChatMsg(MsgID(), UnregisteredID, ServerID, Send_RecvTime(), "", content, MsgType::REGISTER, 1, 1);
    registerMsg.ok = false;
    writeMsg(registerMsg);
}

void Widget::doLogin()
{
    QString content = LoginInfo(loginDlg->uid, loginDlg->pswd).toLoginStr();
    ChatMsg loginMsg = ChatMsg(MsgID(), UnregisteredID, ServerID, Send_RecvTime(), "", content, MsgType::LOGIN, 1, 1);
    loginMsg.ok = false;
    writeMsg(loginMsg);
}

void Widget::satrtRegister()
{
    registerDlg = new RegisterDialog(this);
    qDebug() << connect(registerDlg, &RegisterDialog::canRegister, this, &Widget::doRegister);
    registerDlg->exec();
}

void Widget::startFindPswd()
{
    findpswdDlg = new FindPswdDlg(this);
    qDebug() << connect(findpswdDlg, &FindPswdDlg::couldFindPswd, this, &Widget::doFindPswd);
    findpswdDlg->exec();
}

void Widget::doFindPswd()
{
    QString content = FindPSWDInfo(findpswdDlg->uid, findpswdDlg->key).toFindRequestStr();
    ChatMsg findMsg = ChatMsg(MsgID(), UnregisteredID, ServerID, Send_RecvTime(), "", content, MsgType::FINDPSWD, 1, 1);
    findMsg.ok = false;
    writeMsg(findMsg);
}

void Widget::on_ChangeInfoPBtn_clicked()
{
    ChatMsg userinfoGetMsg = ChatMsg(MsgID(), userid, ServerID, Send_RecvTime(), "", "", MsgType::USERINFG, 1, 1);
    userinfoGetMsg.ok = false;
    writeMsg(userinfoGetMsg);
}

void Widget::showFriendOption(bool showopt)
{
    ui->FriendInfoLEdit->setHidden(!showopt);
    ui->FriendFindPBtn->setHidden(!showopt);
    ui->label->setHidden(!showopt);
}

void Widget::showGroupOption(bool showopt)
{
    ui->label_3->setHidden(!showopt);
    ui->GroupInfoLEdit->setHidden(!showopt);
    ui->GroupFindPBtn->setHidden(!showopt);
    ui->GroupCreatePbtn->setHidden(!showopt);
}

void Widget::on_AddFriendPBtn_clicked()
{
    showFriendOption(true);
    showGroupOption(false);
}

void Widget::on_AddGroupPBtn_clicked()
{
    showFriendOption(false);
    showGroupOption(true);
}

void Widget::on_FriendFindPBtn_clicked()
{
    showFriendOption(false);
}

void Widget::on_GroupFindPBtn_clicked()
{
    showGroupOption(false);
}

void Widget::on_GroupCreatePbtn_clicked()
{
    showGroupOption(false);
}
