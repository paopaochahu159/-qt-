#include "dingwei.h"
#include "ui_dingwei.h"

DingWei::DingWei(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DingWei)
{
    ui->setupUi(this);

}

DingWei::~DingWei()
{
    delete ui;
}

void DingWei::on_pushButton_clicked()
{
    emit dingweiSendData(ui->lineEdit->text());  //获取lineEdit的输入并且传递出去

}

