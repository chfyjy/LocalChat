#include "MsgItem.h"
#include "ui_MsgItem.h"

MsgItem::MsgItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgItem)
{
    ui->setupUi(this);
}

MsgItem::~MsgItem()
{
    delete ui;
}

void MsgItem::on_ReplyPBtn_clicked()
{

}

void MsgItem::on_RequestCBox_currentIndexChanged(int index)
{

}
