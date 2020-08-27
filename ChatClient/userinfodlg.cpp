#include "userinfodlg.h"
#include "ui_userinfodlg.h"

UserInfoDlg::UserInfoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserInfoDlg)
{
    ui->setupUi(this);
}

UserInfoDlg::~UserInfoDlg()
{
    delete ui;
}
