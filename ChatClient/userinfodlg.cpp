#include "userinfodlg.h"
#include "ui_userinfodlg.h"
#include <QMessageBox>
#include <QDebug>

UserInfoDlg::UserInfoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserInfoDlg)
{
    ui->setupUi(this);
    qDebug() << __LINE__;
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    qDebug() << __LINE__;
}

UserInfoDlg::UserInfoDlg(UserInfo info, QWidget *parent):
    QDialog(parent),
    ui(new Ui::UserInfoDlg)
{
    ui->setupUi(this);
    qDebug() << __LINE__;
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    qDebug() << __LINE__;
    uinfo = info;
    qDebug() << __LINE__;
    initUserInfoDlg();
    qDebug() << __LINE__;
}

UserInfoDlg::~UserInfoDlg()
{
    delete ui;
}

void UserInfoDlg::initUserInfoDlg()
{
    if(uinfo.gender)
        ui->ManRBtn->setChecked(true);
    else
        ui->WomanRBtn->setChecked(true);
    ui->AgeLEdit->setText(QString::number(uinfo.age));
    ui->PhoneLEdit->setText(uinfo.phonenum);
    ui->AdressLEdit->setText(uinfo.address);
    ui->birthdayDEdit->setDate(QDate::fromString(uinfo.birthday, datetFmt));
}

void UserInfoDlg::initUserInfo()
{
    if(ui->ManRBtn->isChecked())
        uinfo.gender = true;
    if(ui->WomanRBtn->isChecked())
        uinfo.gender = false;
    uinfo.age = ui->AgeLEdit->text().toInt();
    uinfo.address = ui->AdressLEdit->text();
    uinfo.phonenum = ui->PhoneLEdit->text();
    uinfo.birthday = ui->birthdayDEdit->date().toString(datetFmt);
}

void UserInfoDlg::on_SavePBtn_clicked()
{
    if(!(ui->ManRBtn->isChecked() || ui->WomanRBtn->isChecked()))
    {
        QMessageBox::information(this, "user info", "请选择性别");
        return;
    }
    if(ui->AgeLEdit->text() == "")
    {
        QMessageBox::information(this, "user info", "请输入年龄");
        return;
    }
    if(ui->PhoneLEdit->text() == "")
    {
        QMessageBox::information(this, "user info", "请输入联系方式");
        return;
    }
    if(ui->AdressLEdit->text() == "")
    {
        QMessageBox::information(this, "user info", "请输入地址");
        return;
    }
    initUserInfo();
    emit needPutUserInfo();
}

void UserInfoDlg::on_ClosePBtn_clicked()
{
    close();
}
