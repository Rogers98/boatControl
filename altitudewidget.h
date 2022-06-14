#ifndef ALTITUDEWIDGET_H
#define ALTITUDEWIDGET_H

#include <QChart>
#include <QChartView>
#include <QScatterSeries>
#include <QSplineSeries>
#include <QWidget>

using namespace QtCharts;

namespace Ui {
class AltitudeWidget;
}

class AltitudeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AltitudeWidget(QWidget *parent = nullptr);
    ~AltitudeWidget();

    void timerEvent(QTimerEvent *event);

private:
    Ui::AltitudeWidget *ui;

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
};

#endif // ALTITUDEWIDGET_H
