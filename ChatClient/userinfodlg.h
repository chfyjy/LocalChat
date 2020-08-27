#ifndef USERINFODLG_H
#define USERINFODLG_H

#include <QDialog>

namespace Ui {
class UserInfoDlg;
}

class UserInfoDlg : public QDialog
{
    Q_OBJECT

public:
    explicit UserInfoDlg(QWidget *parent = nullptr);
    ~UserInfoDlg();

private:
    Ui::UserInfoDlg *ui;
};

#endif // USERINFODLG_H
