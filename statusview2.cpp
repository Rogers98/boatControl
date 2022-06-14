#include "statusview2.h"
#include "ui_statusview2.h"

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>

#include <QPropertyAnimation>
#include <QPushButton>
#include <QSignalTransition>
#include <QStateMachine>
#include <QState>
#include <QPainter>
#include <QDebug>
#include <QFile>
#include <QKeyEvent>
#include <QHBoxLayout>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

StatusView2::StatusView2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusView2)
{
    ui->setupUi(this);

//    resize(1680,1000);
    resize(1920, 1013);
    this->setStyleSheet("QWidget#StatusView2{background-color:black;} ");

    // 载入视频
    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _player->setVideoWidget(ui->widget);

    ui->widget->setMediaPlayer(_player);
    ui->widget->setAttribute(Qt::WA_OpaquePaintEvent);
    ui->widget->setUpdatesEnabled(false);

    connect(ui->pushButton_2, &QPushButton::clicked, [=](){
        QString url = "/home/rogers/workspace/test1.mp4";
            if (url.isEmpty())
                return;
        _media = new VlcMedia(url, true, _instance);
        _player->open(_media);
    });


    // 载入地图
    QString htmlPath = QCoreApplication::applicationDirPath() + "/baidumap.html";
    QFile file(htmlPath);
    qDebug() << "网页读取成功，路径为：" <<htmlPath;
    ui->widget_5->load(QUrl("file:///" + htmlPath));

    // 位置
    ui->widget->move(40,0);
    ui->widget->resize(1100,618.75);
    ui->widget->setStyleSheet("QWidget{background-color:#001030;border-radius: 20px;}");

    ui->widget_2->move(40,650);
    ui->widget_2->resize(1100,330);
    ui->widget_2->setStyleSheet("QWidget{border-radius: 30px;}");//background-color:blue;

    ui->widget_3->move(1180,0);
    ui->widget_3->resize(460,230);
    ui->widget_3->setStyleSheet("QWidget#widget_3{background-color:#001030;border-radius: 30px;}");

    ui->widget_4->move(1180,260);
    ui->widget_4->resize(460,460);
    ui->widget_4->setStyleSheet("QWidget{background-color:#001030;border-radius: 30px;}");

    ui->widget_5->move(810,216.5625);
    ui->widget_5->resize(330,185.625);
    ui->widget_5->setStyleSheet("QWidget{background-color:green;border-radius: 10px;}");

    ui->pushButton->move(818,440.125);
    ui->pushButton->setIcon(QIcon(":/res/箭头.png"));
    ui->pushButton->setIconSize(QSize(30, 30));
    ui->pushButton->show();

    QStateMachine *machine = new QStateMachine(this);


//摄像头窗口的动画
    QState * Wid1_Max = new QState(machine);
    Wid1_Max->assignProperty(ui->widget, "geometry", QRect(40, 0, 1100,618.75) );
    machine->setInitialState(Wid1_Max);

    QState * Wid1_Min = new QState(machine);
    Wid1_Min->assignProperty(ui->widget, "geometry", QRect( 810, 433.125, 330, 185.625) );


    QSignalTransition *transition1 = Wid1_Max->addTransition(ui->pushButton,&QPushButton::clicked, Wid1_Min);
    transition1->addAnimation(new QPropertyAnimation(ui->widget, "geometry"));

    QSignalTransition *transition2 = Wid1_Min->addTransition(ui->pushButton,&QPushButton::clicked, Wid1_Max);
    transition2->addAnimation(new QPropertyAnimation(ui->widget, "geometry"));



    //地图窗口的动画
    QStateMachine *machine2 = new QStateMachine(this);

    QState * Wid2_Min = new QState(machine2);
    Wid2_Min->assignProperty(ui->widget_5,"geometry", QRect( 810,433.125 , 330,185.625) );
    machine2->setInitialState(Wid2_Min);

    QState * Wid2_Max = new QState(machine2);
    Wid2_Max->assignProperty(ui->widget_5,"geometry", QRect(40, 0, 1100,618.75));


    QSignalTransition * transition3 = Wid2_Min->addTransition(ui->pushButton,&QPushButton::clicked, Wid2_Max);
    transition3->addAnimation(new QPropertyAnimation(ui->widget_5, "geometry") );

    QSignalTransition * transition4 = Wid2_Max->addTransition(ui->pushButton,&QPushButton::clicked, Wid2_Min);
    transition4->addAnimation(new QPropertyAnimation(ui->widget_5, "geometry") );

    machine->start();
    machine2->start();

    //前后位置变化
    connect( ui->pushButton , &QPushButton::clicked , this , [=](){

        if(ui->widget->width()>ui->widget_5->width())
            ui->widget->raise();
        else
            ui->widget_5->raise();
        ui->pushButton->raise();

    });


    //键盘事件触发界面的变化
    QTimer * Update_Timer = new QTimer;
    Update_Timer->setInterval(100);
    Update_Timer->start();
    connect(Update_Timer , SIGNAL(timeout()) , this , SLOT(PanleUpdate()) );
    this->m_state = 0;


    // 绘制折线图
    addChart();

    QLineSeries *series = new QLineSeries();

    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPoint(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
//    chart->setTitle("hello world");

    ui->widget_4->setChart(chart);
    ui->widget_4->setRenderHint(QPainter::Antialiasing);
}

StatusView2::~StatusView2()
{
    delete ui;
}

void StatusView2::paintEvent(QPaintEvent *event)
{

}

void StatusView2::keyPressEvent(QKeyEvent *event)
{

    if( event->key() == Qt::Key_W )
    {
        ui->widget_2->setNowState(2);
    }

    if( event->key() == Qt::Key_S )
    {
        ui->widget_2->setNowState(3);
    }

    if( event->key() == Qt::Key_P )
    {
        ui->widget_2->setNowState(1);
    }


    if( event->key() == Qt::Key_A)
    {
        this->m_state += 1;
        float state = ui->widget_2->getDeltaAngle();
        if(state>=-90)
        {
            state -= 1;
//            qDebug()<<state;
            ui->widget_2->setDeltaAngle(state);
        }
    }

    if( event->key() == Qt::Key_D)
    {
        this->m_state += 1;
        float state = ui->widget_2->getDeltaAngle();
        if(state<=90)
        {
            state += 1;
//            qDebug()<<state;
            ui->widget_2->setDeltaAngle(state);
        }
    }

}
void StatusView2::setSpeed(float _speed)
{
    NowSpeed = _speed;
}

void StatusView2::PanleUpdate()
{
    double ShowingSpeed = ui->widget_2->getNowSpeed();
    //速度25不掉帧
    if(NowSpeed>=ShowingSpeed)
    {
        ShowingSpeed += 10;
        ui->widget_2->setNowSpeed(ShowingSpeed);

    }
    else if(NowSpeed <= ShowingSpeed )
    {
        ShowingSpeed -= 10 ;
        ui->widget_2->setNowSpeed(ShowingSpeed);
    }
    update();
}

//
void StatusView2::addChart()
{
//    QLineSeries *series = new QLineSeries();

//    series->append(0, 6);
//    series->append(2, 4);
//    series->append(3, 8);
//    series->append(7, 4);
//    series->append(10, 5);
//    *series << QPointF(11, 1) << QPointF(13, 3) << QPoint(17, 6) << QPointF(18, 3) << QPointF(20, 2);

//    QChart *chart = new QChart();
//    chart->legend()->hide();
//    chart->addSeries(series);
//    chart->createDefaultAxes();

    maxSize = 31; // 只存储最新的 31 个数据
    maxX = 300;
    maxY = 100;

    splineSeries = new QSplineSeries();
    lineSeries = new QLineSeries();
    scatterSeries = new QScatterSeries();
    scatterSeries->setMarkerSize(8);

    chart = new QChart();
//    chart->addSeries(splineSeries);
    chart->addSeries(lineSeries);
    chart->addSeries(scatterSeries);
    chart->legend()->hide();
    chart->setTitle(QStringLiteral("实时动态曲线"));
    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 300);
    chart->axisY()->setRange(0, maxY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

//    QHBoxLayout *layout = new QHBoxLayout();
//    layout->setContentsMargins(0, 0, 0, 0);
//    layout->addWidget(chartView);
//    setLayout(layout);

    timerId = startTimer(500);
    qsrand(QDateTime::currentDateTime().toTime_t());

    ui->widget_3->setChart(chart);
    ui->widget_3->setRenderHint(QPainter::Antialiasing);
}

void StatusView2::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId) {
        int newData = qrand() % (maxY + 1);
        dataReceived(newData);
    }
}


void StatusView2::dataReceived(int value)
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

