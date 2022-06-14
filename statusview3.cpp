#include "statusview3.h"
#include "getserialdata.h"
#include "ui_statusview3.h"

#include <QSplitter>
#include <QTextEdit>
#include <QList>
#include <QWebEngineView>
#include <QWebChannel>
#include <QMessageBox>
#include <QDebug>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>

StatusView3::StatusView3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusView3)
{
    ui->setupUi(this);
    resize(1920, 1013);


   QSplitter* splitterMain = new QSplitter(Qt::Vertical,this);
   splitterMain->setFixedSize(1920, 1013);
   QSplitter* splitterTop = new QSplitter(Qt::Horizontal, splitterMain);

   // 使用QWebChannel使得js和widget交互
   QWebChannel *m_pWebChannel = new QWebChannel(this);
   m_pWebChannel->registerObject(QString("qtui"), this);
   ui->mapWidget->page()->setWebChannel(m_pWebChannel);

   // 载入地图
   //mapWidget->load(QUrl());
   QString htmlPath = QCoreApplication::applicationDirPath() + "/amap2.html";
   QFile file(htmlPath);
   qDebug() << "网页读取成功，路径为：" <<htmlPath;
   ui->mapWidget->load(QUrl("file:///" + htmlPath));


   // 载入视频
   _instance = new VlcInstance(VlcCommon::args(), this);
   _player = new VlcMediaPlayer(_instance);
   _player->setVideoWidget(ui->videoPlayWidget);

   ui->videoPlayWidget->setMediaPlayer(_player);
   ui->videoPlayWidget->setAttribute(Qt::WA_OpaquePaintEvent);
   ui->videoPlayWidget->setUpdatesEnabled(false);


//   将刚刚载入的空间显示在splitter分割的窗口上，并设置一些大小和样式
   splitterTop->addWidget(ui->mapWidget);
   splitterTop->addWidget(ui->videoWidget);
   splitterMain->addWidget(ui->statusWidget);
   QList<int> listVertical, listHorizontal, videolist;
   listVertical << 613 << 400;     // 垂直分割高的尺寸
   splitterMain->setSizes(listVertical);
   listHorizontal << 960 << 960;  //水平分割宽的尺寸
   splitterTop->setSizes(listHorizontal);
   videolist << 563 << 50;
   ui->mapWidget->resize(960, 613);

    getData = new getSerialData();
    getData->show();
//    getData->openPort();

    // 每100ms刷新一次IMU数据
    QTimer *timer = new QTimer(this);
    timer->start(100);
    connect(timer, &QTimer::timeout,[=](){
        QByteArray IMUData = getData->getIMUData();
        if (IMUData.length()>0) {
            QStringList list = QString(IMUData).split(",");
            double angle = (list[0].mid(1).toDouble())/10;
            qDebug() << IMUData;
            QString ax = QString::number(list[1].toDouble()/16384.0,'f',4);
            QString ay = QString::number((list[2].toDouble())/16384.0,'f',4);
            QString az = QString::number(list[3].toDouble()/16384.0,'f',4);
            ui->angle_label->setNum(angle);
            ui->ax_label->setText(ax);
            ui->ay_label->setText(ay);
            ui->az_label->setText(az);
        }
    });


}

StatusView3::~StatusView3()
{
    delete ui;
}

void StatusView3::on_playButton_clicked()
{
//    if (libvlc_Ended == libvlc_media_get_state(_media))
    QString url = ui->videoAddEdit->text();

    // 地址1：/home/rogers/workspace/test1.mp4
    // 地址2：rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov
    // 地址3：http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8
    // 地址4：rtmp://58.200.131.2:1935/livetv/cctv1
    if (url.isEmpty())
    {
//        QMessageBox::information(NULL, "提示", "地址为空，默认播放测试视频", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
        _media = new VlcMedia("/home/rogers/workspace/test2.MOV", true, _instance);
//        return;
    }
    else if (url.startsWith("rtsp") || url.startsWith("rtmp") || url.endsWith("m3u8")) {
        _media = new VlcMedia(url, _instance);
        qDebug() << "进入网络流";
    }
    else if (url.startsWith("/home")) {
        _media = new VlcMedia(url, true, _instance);
        qDebug() << "进入本地视频";
    } else {
//        _media = new VlcMedia("/home/rogers/workspace/test1.mp4", true, _instance);
        QMessageBox::information(NULL, "提示", "地址错误", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
        return;
    }
    _player->open(_media);

}

void StatusView3::on_stopButton_clicked()
{
    _player->stop();
}

void StatusView3::fromJsCallQt()
{
    qDebug() << "qt:来自html的调用";
    this->fromQtCallJs();

}

void StatusView3::fromQtCallJs() {
    QString x1="113.395774", y1="23.034974", x2="113.39579", y2="23.035616";
    QString jsStr = "drawPositionLine(" + x1 + "," + y1 + "," + x2 + "," + y2 +")";
    qDebug() << jsStr;
    ui->mapWidget->page()->runJavaScript(jsStr);
}
