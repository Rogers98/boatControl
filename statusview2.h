#ifndef STATUSVIEW2_H
#define STATUSVIEW2_H

#include <QChart>
#include <QChartView>
#include <QScatterSeries>
#include <QSplineSeries>
#include <QWidget>

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

using namespace QtCharts;

namespace Ui {
class StatusView2;
}

class StatusView2 : public QWidget
{
    Q_OBJECT

public:
    explicit StatusView2(QWidget *parent = 0);
    ~StatusView2();

    void paintEvent(QPaintEvent * event);
    void keyPressEvent(QKeyEvent * event);
    // 速度变化函数
    void setSpeed(float _speed);
    // 添加图表的函数与时间监听器
    void addChart();
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

private:
    float NowSpeed;

    // 直播视频变量
    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;
    int m_state;

    //  接收到数据源发送来的数据，数据源可以下位机，采集卡，传感器等。
   void dataReceived(int value);

   // 图表的变量
   int timerId;
   int maxSize;  // data 最多存储 maxSize 个元素
   int maxX;
   int maxY;
   QList<double> data; // 存储业务数据的 list

   QChart *chart;
   QChartView *chartView;
   QSplineSeries *splineSeries;
   QLineSeries *lineSeries;
   QScatterSeries *scatterSeries;



private:
    Ui::StatusView2 *ui;

public slots:
    void PanleUpdate();


};

#endif // WIDGET_H
