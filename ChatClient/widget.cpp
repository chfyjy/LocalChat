#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    chatsession = new ChatSession(this);
    chatsession->startThread();

    //loginDlg = new LoginDialog(this);
    //loginDlg->exec();
}

Widget::~Widget()
{
    delete ui;
}

