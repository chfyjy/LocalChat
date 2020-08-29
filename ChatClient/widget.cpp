#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initSocket();
    loginDlg = new LoginDialog(this);
    qDebug() << connect(loginDlg, &LoginDialog::needRegister, this, &Widget::satrtRegister);
    qDebug() << connect(loginDlg, &LoginDialog::needLogin, this, &Widget::doLogin);
    qDebug() << connect(loginDlg, &LoginDialog::needFindPswd, this, &Widget::startFindPswd);
    loginDlg->exec();
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
    if(msg.ok != true)
        return;
    QMessageBox::information(this, "register", msg.content);
    loginDlg->doRegisterDone();
}
void Widget::loginHandle(ChatMsg msg)
{
    if(msg.ok == true)
    {
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

void Widget::MessageHandling(ChatMsg msg)
{
    switch (msg.msgtype)
    {
    case MsgType::REGISTER:registerHandle(msg);break;
    case MsgType::LOGIN   :loginHandle(msg);break;
    case MsgType::FINDPSWD:findPswdHandle(msg);break;
    case MsgType::USERINFO:break;
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

}
