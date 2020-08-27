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
    if(!chatdb->createTables())
    {
        qDebug() << chatdb->lastErrorString();
        exit(0);
    }
    chatdb->deleteLater();

    chatserver = new ChatServer(this);

    if(!chatserver->listen(QHostAddress(QHostAddress::Any), ServerPort))
    {
        qDebug() << "listen error";
        exit(0);
    }
    else
        qDebug() << "listened";

}

MainWindow::~MainWindow()
{
    chatserver->deleteLater();
    delete ui;
}

