#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QNetworkRequest>
#include<QHostAddress>
#include<QFile>
#include<QMessageBox>
#include<QDialog>

#include<QNetworkInterface>
#include<QNetworkReply>

#include<QJsonParseError>
#include<QJsonObject>
#include<QJsonArray>

#include"dingwei.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void dingweiData(QString data);   //接收传递过来的数据的槽

    void dingWei(QNetworkReply*);
    QString findCityId(const QString &cityName);//查找城市id
    void Get_Information(QString id );
    void realTime(QNetworkReply*);//处理实时天气信息


    // void dealMsg(QNetworkReply * reply);

private:
    Ui::MainWindow *ui;

    //天气情况对应的图标
    QHash<QString, QString> W ={
        {"晴",":/weather/img/weather/sunny-light.png"},
        {"晴1",":/weather/img/weather/sunny-night.png"},
        {"多云",":/weather/img/weather/cloudy-light.png"},
        {"多云1",":/weather/img/weather/cloudy-night.png"},
        {"小雨",":/weather/img/weather/moderate rain.png"},
        {"中雨",":/weather/img/weather/heavy rain.png"},
        {"大雨",":/weather/img/weather/rainstorm.png"},
        {"阴",":/weather/img/weather/Overcast sky.png"},
        {"雪",":/weather/img/weather/snow.png"},
    };
};
#endif // MAINWINDOW_H
