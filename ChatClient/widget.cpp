#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initSocket();
    loginDlg = new LoginDialog(this);
    qDebug() << connect(loginDlg, &LoginDialog::needRegister, this, &Widget::satrtRegister);
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
    qDebug() << socket->readAll();
    qDebug() << "";
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
    qDebug() << registerDlg->nickname;
    qDebug() << registerDlg->pswd;
    qDebug() << registerDlg->key1;
    qDebug() << registerDlg->key2;
    QString mid = MsgID();
    QString content = RegisterInfo(registerDlg->nickname, registerDlg->pswd, registerDlg->key1, registerDlg->key2).toRegisterStr();
    ChatMsg registerMsg = ChatMsg(mid, UnregisteredID, ServerID, Send_RecvTime(), "", content, MsgType::REGISTER, 1, 1);
    writeMsg(registerMsg);
}

void Widget::satrtRegister()
{
    registerDlg = new RegisterDialog(this);
    qDebug() << connect(registerDlg, &RegisterDialog::canRegister, this, &Widget::doRegister);
    registerDlg->exec();
}
