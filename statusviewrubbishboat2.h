#ifndef STATUSVIEWRUBBISHBOAT2_H
#define STATUSVIEWRUBBISHBOAT2_H

#include <QWidget>
#include "getserialdata.h"

#include "QLabel"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "QFile"

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

namespace Ui {
class StatusViewRubbishBoat2;
}

class StatusViewRubbishBoat2 : public QWidget
{
    Q_OBJECT

public:
    explicit StatusViewRubbishBoat2(QWidget *parent = nullptr);
    ~StatusViewRubbishBoat2();

    void setIMUData();
    getSerialData *getData;
    void fromQtCallJs();

    // opencv播放函数
    void LabelDisplayMat(QLabel *label, cv::Mat &mat);
    void playVideo();

    void setRecvDataView(QByteArray data);

private:
    Ui::StatusViewRubbishBoat2 *ui;
    // 直播视频变量
    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;
    int m_state;

    // socket直播视频变量
//    int ServerFd;

    // 清洁船的控制数据
    QByteArray rubbishBoatControlData;

    QByteArray rubbishBoatRecvData;

    // 清洁船的显示数据
    float accX = 0.; // 加速度X方向
    float accY = 0.; // 加速度Y方向
    float accZ = 0.; // 加速度Z方向
    float gyrX = 0.; // 陀螺仪X轴
    float gyrY = 0.; // 陀螺仪Y轴
    float gyrZ = 0.; // 陀螺仪Z轴
    float pitch = 0.; // 欧拉角pitch
    float roll = 0.; // 欧拉角roll
    float yaw = 0.; // 欧拉角yaw
    double lng = 0.; // 经度longtitude
    double lat = 0.; // 纬度latitude

    bool modeBool = false;

//    QFile recvFile;


private slots:
    void on_playButton_clicked();
    void on_stopButton_clicked();
    void on_pushButton_4_clicked();
public slots:
    void fromJsCallQt();
    void recvDataFromSerial();

protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // STATUSVIEWRUBBISHBOAT2_H
