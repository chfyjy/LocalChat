#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    QString uid, pswd;
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    void doRegisterDone();

private slots:
    void on_RegisterPBtn_clicked();
    void on_LoginPBtn_clicked();

    void on_FindPswdPBtn_clicked();

signals:
    void needRegister();
    void needLogin();
    void needFindPswd();
private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
