#ifndef DINGWEI_H
#define DINGWEI_H

#include <QDialog>
#include<QComboBox>

#include <QMainWindow>
#include<QNetworkRequest>
#include<QHostAddress>

#include<QNetworkInterface>
#include<QNetworkReply>

#include<QJsonParseError>
#include<QJsonObject>
#include<QJsonArray>

namespace Ui {
class DingWei;
}

class DingWei : public QDialog
{
    Q_OBJECT

public:
    explicit DingWei(QWidget *parent = nullptr);
    ~DingWei();

signals:
    void dingweiSendData(QString);//用来传递数据的信号

private slots:
    void on_pushButton_clicked();

private:
    Ui::DingWei *ui;
};

#endif // DINGWEI_H
