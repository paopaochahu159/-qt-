#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //获得地理位置
    QNetworkAccessManager* m = new QNetworkAccessManager;//用于发送和处理网页信息
    QNetworkRequest weizhiAPI(QString("https://myip.ipip.net/"));
    connect(m, SIGNAL(finished(QNetworkReply*)), this,SLOT(dingWei(QNetworkReply*)));
    m->get(weizhiAPI);
}

void MainWindow::dingWei(QNetworkReply* reply){
    QString all = reply->readAll();
    QString id = findCityId(all.split(' ')[5] + "市");
    if (id.size() < 6){
        QMessageBox::warning(this, "警告", "id错误");
        return;
    }
    Get_Information(id);
}

void MainWindow::Get_Information(QString id){
    //请求json数据
    QNetworkAccessManager* m = new QNetworkAccessManager;//用于发送和处理网页信息
    QNetworkRequest weizhiAPI;
    // QUrl url;
    // url.setUrl( QString("https://restapi.amap.com/v3/weather/weatherInfo?city=%1&key=cc134ef36f7ea51d3f3e677e824356c5").arg(id));
    //设置请求的url
    weizhiAPI.setUrl(QString("https://restapi.amap.com/v3/weather/weatherInfo?city=%1&key=cc134ef36f7ea51d3f3e677e824356c5").arg(id));

    connect(m, SIGNAL(finished(QNetworkReply*)), this,SLOT(realTime(QNetworkReply*)));
    //finished 信号用于通知应用程序网络请求已完成
    //当我们发送完请求后接收到数据 自动调用realTime函数 并且自动传递数据过去
    m->get(weizhiAPI);//发送get请求
}

void MainWindow::realTime(QNetworkReply* reply){//解析天气信息并且显示
    QString all = reply->readAll();
    // QJsonParseError类用于在JSON解析期间报告错误。
    QJsonParseError jsonError;
    // 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
    // 如果解析成功，返回QJsonDocument对象，否则返回null
    QJsonDocument doc = QJsonDocument::fromJson(all.toUtf8(), &jsonError);
    // 判断是否解析失败
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
        QMessageBox::warning(this, "警告", "解析失败");
        return;
    }
    QJsonObject rootObj = doc.object();
    QJsonObject lives = rootObj.value("lives").toArray()[0].toObject();//解析出实时天气信息

    ui->label->setText(lives.value("province").toString() + "-" + lives.value("city").toString());//当前城市
    ui->label_6->setText(lives.value("weather").toString());//天气文字描述
    ui->label_3->setText(lives.value("temperature").toString());//当前温度
    ui->label_5->setText(lives.value("winddirection").toString() + "风" + lives.value("windpower").toString() + "级");

    //判断当前时间 实现时间段切换
    QString currentTime = QTime::currentTime().toString();
    // currentTime = "18:00:50";
    if (currentTime > "06::00::00" && currentTime < "18:00:00"){
        ui->label_2->setPixmap(W[lives.value("weather").toString()]);//设置天气图标
    }
    else{
        QString tianqi1 = lives.value("weather").toString();

        if (tianqi1[0] == "晴" ||  tianqi1[0] == "多") ui->label_2->setPixmap(W[tianqi1 + "1"]);
        else ui->label_2->setPixmap(W[tianqi1]);

        this->setStyleSheet("QMainWindow {background-image:url(:/img/img/yewanbeij.jpg)}");//设置背景
    }
    // 获取当前日期
    QDate currentDate = QDate::currentDate();
    // 创建一个中文本地化对象
    QLocale chineseLocale(QLocale::Chinese, QLocale::China);
    // 使用中文本地化对象格式化日期和时间
    QString dateString = chineseLocale.toString(currentDate, "yyyy年MM月dd日 dddd");
    ui->label_7->setText(dateString);
    ui->label_8->setText(currentTime);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//切换城市
void MainWindow::on_pushButton_clicked()
{
    DingWei *dingwei  = new DingWei(this);
    connect(dingwei, SIGNAL(dingweiSendData(QString)), this, SLOT(dingweiData(QString)));//关联输出和接收函数

    dingwei->setWindowModality(Qt::ApplicationModal);
    dingwei->setFixedSize(380, 100);
    dingwei->show();
    return;
}
void MainWindow::dingweiData(QString data){//接收函数
    QString id = findCityId(data);
    if (id.size() < 6){
        QMessageBox::warning(this, "警告", "id错误");
        return;
    }
    Get_Information(id);
}
QString MainWindow::findCityId(const QString &cityName){//在数据库里查找城市id
    QFile file(":/new/prefix1/cityID.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件";
        return QString();
    }

    QTextStream in(&file);
    while (!in.atEnd()) {//检测读取指针是否到最底部
        QString line = in.readLine();//从最上方开始读取未读数据 已读的跳过
        QStringList fields = line.split(',');
        // qDebug() << fields[0][1];
        if (fields.size() >= 2 && fields[0] == cityName) {
            return fields[1]; // 返回城市ID
        }
    }

    file.close();
    return "a";
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "254";
}
