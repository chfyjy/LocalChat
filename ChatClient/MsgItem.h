#ifndef MSGFORM_H
#define MSGFORM_H

#include <QWidget>

namespace Ui {
class MsgItem;
}

class MsgItem : public QWidget
{
    Q_OBJECT

public:
    explicit MsgItem(QWidget *parent = nullptr);
    ~MsgItem();

private slots:
    void on_ReplyPBtn_clicked();

    void on_RequestCBox_currentIndexChanged(int index);

private:
    Ui::MsgItem *ui;
};

#endif // MSGFORM_H
