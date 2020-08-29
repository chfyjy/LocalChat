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

private:
    Ui::DataCard *ui;
};

#endif // DATACARD_H
