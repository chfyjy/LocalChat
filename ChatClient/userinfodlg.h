#ifndef USERINFODLG_H
#define USERINFODLG_H

#include <QDialog>
#include "../common/ChatCtrl.h"

namespace Ui {
class UserInfoDlg;
}

class UserInfoDlg : public QDialog
{
    Q_OBJECT

public:
    UserInfo uinfo;
    explicit UserInfoDlg(QWidget *parent = nullptr);
    explicit UserInfoDlg(UserInfo uinfo, QWidget *parent = nullptr);
    ~UserInfoDlg();
    void initUserInfoDlg();
signals:
    void needPutUserInfo();

private slots:
    void on_SavePBtn_clicked();

    void on_ClosePBtn_clicked();

    void initUserInfo();

private:
    Ui::UserInfoDlg *ui;
};

#endif // USERINFODLG_H
