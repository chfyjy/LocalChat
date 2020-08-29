#ifndef DATACARD_H
#define DATACARD_H

#include <QWidget>

namespace Ui {
class DataCard;
}

class DataCard : public QWidget
{
    Q_OBJECT

public:
    explicit DataCard(QWidget *parent = nullptr);
    ~DataCard();

private slots:
    void on_ChangePBtn_clicked();

    void on_SavePBtn_clicked();

    void on_closePBtn_clicked();

private:
    Ui::DataCard *ui;
};

#endif // DATACARD_H
