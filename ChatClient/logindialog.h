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
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    void doRegisterDone();

private slots:
    void on_RegisterPBtn_clicked();
    void on_LoginPBtn_clicked();

signals:
    void needRegister();
    void needLogin();
private:
    Ui::LoginDialog *ui;
    QString uid, pswd;
};

#endif // LOGINDIALOG_H
