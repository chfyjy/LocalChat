#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

bool RegisterDialog::couldRegister()
{
    if(ui->NicknameLEdit->text() == "")
    {    QMessageBox::information(this, "Tip", "昵称请勿为空");
        return false;
    }
    if(ui->PswdLEdit->text() == "")
    {
        QMessageBox::information(this, "Tip", "密码请勿为空");
        return false;
    }
    if(ui->PkeyLEdit1->text() == "")
    {
        QMessageBox::information(this, "Tip", "密保1请勿为空");
        return false;
    }
    if(ui->PkeyLEdit2->text() == "")
    {
        QMessageBox::information(this, "Tip", "密保2请勿为空");
        return false;
    }
    return true;
}
void RegisterDialog::on_RegisterPBtn_clicked()
{
    if(!couldRegister())
        return;
    nickname = ui->NicknameLEdit->text();
    pswd = ui->PswdLEdit->text();
    key1 = ui->PkeyLEdit1->text();
    key2 = ui->PkeyLEdit2->text();
    emit canRegister();
}
