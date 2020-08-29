#ifndef DINDPSWDDLG_H
#define DINDPSWDDLG_H

#include <QDialog>

namespace Ui {
class FindPswdDlg;
}

class FindPswdDlg : public QDialog
{
    Q_OBJECT

public:
    QString uid, key;
    explicit FindPswdDlg(QWidget *parent = nullptr);
    ~FindPswdDlg();
signals:
    void couldFindPswd();
private slots:
    void on_FindPBtn_clicked();

private:
    Ui::FindPswdDlg *ui;
};

#endif // DINDPSWDDLG_H
