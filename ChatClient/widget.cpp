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
    qDebug() << connect(loginDlg, &LoginDialog::needLogin, this, &Widget::satrtRegister);
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

void Widget::MessageHandling(ChatMsg msg)
{
    switch (msg.msgtype)
    {
    case MsgType::REGISTER:registerHandle(msg);break;
    case MsgType::FINDPSWD:break;
    case MsgType::USERINFO:break;
    case MsgType::TEXTMSG :break;
    case MsgType::FILEMSG :break;
    case MsgType::FRIENDA :break;
    case MsgType::FRIENDF :break;
    case MsgType::FRIENDD :break;
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
    QString mid = MsgID();
    QString content = RegisterInfo(registerDlg->nickname, registerDlg->pswd, registerDlg->key1, registerDlg->key2).toRegisterStr();
    ChatMsg registerMsg = ChatMsg(mid, UnregisteredID, ServerID, Send_RecvTime(), "", content, MsgType::REGISTER, 1, 1);
    registerMsg.ok = false;
    writeMsg(registerMsg);
}

void Widget::satrtRegister()
{
    registerDlg = new RegisterDialog(this);
    qDebug() << connect(registerDlg, &RegisterDialog::canRegister, this, &Widget::doRegister);
    registerDlg->exec();
}
