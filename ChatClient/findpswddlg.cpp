#include "findpswddlg.h"
#include "ui_findpswddlg.h"
#include <QMessageBox>

const QString title = "Find The Password";

FindPswdDlg::FindPswdDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindPswdDlg)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowTitle(title);
}

FindPswdDlg::~FindPswdDlg()
{
    delete ui;
}

void FindPswdDlg::on_FindPBtn_clicked()
{
    if(ui->UIDLEdit->text() == "")
    {
        QMessageBox::information(this, title, "请输入账号");
        return;
    }
    if(ui->KeyLEdit->text() == "")
    {
        QMessageBox::information(this, title, "请输入任一密保");
        return;
    }
    uid = ui->UIDLEdit->text();
    key = ui->KeyLEdit->text();
    emit couldFindPswd();
}
