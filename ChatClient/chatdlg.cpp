#include "chatdlg.h"
#include "ui_chatdlg.h"

ChatDlg::ChatDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatDlg)
{
    ui->setupUi(this);
}

ChatDlg::~ChatDlg()
{
    delete ui;
}
