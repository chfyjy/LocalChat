#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_RegisterPBtn_clicked()
{
    emit needRegister();
    //ui->RegisterPBtn->setEnabled(false);
}

void LoginDialog::doRegisterDone()
{
    //ui->RegisterPBtn->setEnabled(true);
    qDebug() << "ui->RegisterPBtn->setEnabled(true);";
}

void LoginDialog::on_LoginPBtn_clicked()
{
    uid = ui->AccountCbBox->currentText();
    pswd = ui->PswdLEdit->text();
    emit needLogin();
}

void LoginDialog::on_FindPswdPBtn_clicked()
{
    emit needFindPswd();
}
