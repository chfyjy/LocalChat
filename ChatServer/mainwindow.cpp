#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "../common/ChatCtrl.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chatdb = new ChatDataBase(this);
    qDebug() << chatdb->createTables() << chatdb->lastErrorString();
    chatserver = new ChatServer(this);
    ;
    if(!chatserver->listen(QHostAddress(QHostAddress::Any), ServerPort))
        qDebug() << "listen error";
    else
        qDebug() << "listened";

}

MainWindow::~MainWindow()
{
    chatserver->deleteLater();
    chatdb->deleteLater();
    delete ui;
}

