#include "userinfodlg.h"
#include "ui_userinfodlg.h"

UserInfoDlg::UserInfoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserInfoDlg)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
}

UserInfoDlg::UserInfoDlg(UserInfo uinfo, QWidget *parent):
    QDialog(parent),
    ui(new Ui::UserInfoDlg)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    if(uinfo.gender)
        ui->ManRBtn->setDown(true);
    else
        ui->WomanRBtn->setDown(true);
    ui->AgeLEdit->setText(QString::number(uinfo.age));
    ui->PhoneLEdit->setText(uinfo.phonenum);
    ui->AdressLEdit->setText(uinfo.address);
    ui->birthdayDEdit->setDate(QDate::fromString(uinfo.birthday, datetFmt));
}

UserInfoDlg::~UserInfoDlg()
{
    delete ui;
}
