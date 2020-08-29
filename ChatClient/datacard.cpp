#include "datacard.h"
#include "ui_datacard.h"

DataCard::DataCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataCard)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
}

DataCard::~DataCard()
{
    delete ui;
}
