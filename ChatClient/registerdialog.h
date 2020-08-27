#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();
    QString nickname, pswd, key1, key2;
private slots:
    void on_RegisterPBtn_clicked();
signals:
    void canRegister();
private:
    bool couldRegister();
private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
