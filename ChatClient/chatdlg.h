#ifndef CHATDLG_H
#define CHATDLG_H

#include <QWidget>

namespace Ui {
class ChatDlg;
}

class ChatDlg : public QWidget
{
    Q_OBJECT

public:
    explicit ChatDlg(QWidget *parent = nullptr);
    ~ChatDlg();

private:
    Ui::ChatDlg *ui;
};

#endif // CHATDLG_H
