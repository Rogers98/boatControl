#include "altitudewidget.h"
#include "ui_altitudewidget.h"

#include <QTime>

AltitudeWidget::AltitudeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AltitudeWidget)
{
    ui->setupUi(this);
    maxSize = 31; // 只存储最新的 31 个数据
    maxX = 30;
    maxY = 100;

    splineSeries = new QSplineSeries();
    lineSeries = new QLineSeries();
    scatterSeries = new QScatterSeries();
    scatterSeries->setMarkerSize(0);

    chart = new QChart();
    chart->setBackgroundVisible(false);
    setStyleSheet(R"(QGraphicsView{background-color:black)})");
//    chart->addSeries(splineSeries);
    chart->addSeries(lineSeries);
    chart->addSeries(scatterSeries);
    chart->legend()->hide();
    chart->setTitle(QStringLiteral("Z轴转速(rad/s)"));
    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 30);
    chart->axisY()->setRange(0, maxY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

//    QHBoxLayout *layout = new QHBoxLayout();
//    layout->setContentsMargins(0, 0, 0, 0);
//    layout->addWidget(chartView);
//    setLayout(layout);

    timerId = startTimer(500);
    qsrand(QDateTime::currentDateTime().toTime_t());

    ui->chartWidget->setChart(chart);
    ui->chartWidget->setRenderHint(QPainter::Antialiasing);
}

AltitudeWidget::~AltitudeWidget()
{
    delete ui;
}

void AltitudeWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId) {
        int newData = 70- (qrand() % 5);
        dataReceived(newData);
    }
}

void AltitudeWidget::dataReceived(int value)
{
    data << value;

    while(data.size() > maxSize)
    {
        data.removeFirst();
    }

    // 界面被隐藏后就没有必要绘制数据的曲线了
    if (isVisible()) {
        splineSeries->clear();
        scatterSeries->clear();
        lineSeries->clear();
        int dx = maxX / (maxSize-1);
        int less = maxSize - data.size();

        for (int i = 0; i < data.size(); ++i) {
            splineSeries->append(less*dx+i*dx, data.at(i));
            scatterSeries->append(less*dx+i*dx, data.at(i));
            lineSeries->append(less*dx+i*dx, data.at(i));
        }
    }
}
