#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "statusview.h"
#include "ui_statusview.h"


#include <QFile>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QWebChannel>
#include <ctime>
#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->resize(1920, 1080);
    setWindowIcon(QIcon(":/res/uav.png"));
    setWindowTitle("ground control");

    // 使用QWebChannel使得js和widget交互
    QWebChannel *m_pWebChannel = new QWebChannel(this);
    m_pWebChannel->registerObject(QString("qtui"), this);
    ui->widget_map->page()->setWebChannel(m_pWebChannel);

    // 载入地图网页
//    QString htmlPath = QCoreApplication::applicationDirPath() + "/baidumap.html";
    QString htmlPath = QCoreApplication::applicationDirPath() + "/amap_main.html";
    QFile file(htmlPath);
    qDebug() << htmlPath;
    ui->widget_map->load(QUrl("file:///" + htmlPath));
    // ui->widget_map->setStyleSheet("border-radius:15px");
    // TODO: 载入网页的第二种方法（存在问题），问题如下
    // QUrl这样设置的话会在html中提示找不到webchannel资源
    // ui->widget_map->load(QUrl("qrc:/res/amap_main.html"));

    QPushButton *pBtn = ui->widget_8->findChild<QPushButton*>("pushButton");
    connect(pBtn, &QPushButton::clicked, [=](){
        double x = 126.6447, y = 45.7266;
        QString jsStr = "addCircle(" + QString::number(x) + "," + QString::number(y) + ")";
        qDebug() << jsStr;
        sView->ui->widget_map2->page()->runJavaScript(jsStr);
    });

//    pBtn->setStyleSheet("border:2px groove white;border-radius:10px;background-color:gray;");

    this->sView2 = new StatusView2();
    this->sView = new statusView();
    this->sView3 = new StatusView3();
    connect(sView, &statusView::sendMessageToMainWindow, this, &MainWindow::recievePositionSignal);



    // 设置一些样式
    ui->label->setStyleSheet("color:white");
    ui->label_2->setStyleSheet("color:white");
    ui->label_3->setStyleSheet("color:white");
    ui->label_4->setStyleSheet("color:white");
    ui->label_5->setStyleSheet("color:white");

    ui->label_6->setStyleSheet("color:white;font-size:17px;");
    ui->label_7->setStyleSheet("color:white;font-size:17px;");
    ui->label_8->setStyleSheet("color:white;font-size:17px;");
    ui->label_9->setStyleSheet("color:white;font-size:17px;");
    ui->label_10->setStyleSheet("color:white;font-size:17px;");
    ui->label_11->setStyleSheet("color:white;font-size:17px;");

    ui->label_12->setStyleSheet("color:white;font-size:25px;");
    ui->label_13->setStyleSheet("color:white;font-size:25px;");

    ui->widget_3->findChild<QLabel*>("label_5")->setText(QStringLiteral("离线"));
    ui->widget_6->findChild<QLabel*>("label_5")->setText(QStringLiteral("离线"));
    ui->widget_1->findChild<QProgressBar*>("progressBar")->setValue(90);
    ui->widget_2->findChild<QProgressBar*>("progressBar")->setValue(60);
    ui->widget_3->findChild<QProgressBar*>("progressBar")->setValue(0);
    ui->widget_4->findChild<QProgressBar*>("progressBar")->setValue(70);
    ui->widget_5->findChild<QProgressBar*>("progressBar")->setValue(30);
    ui->widget_6->findChild<QProgressBar*>("progressBar")->setValue(0);

    // 设置计时器，一秒更新一次，以显示时间
    // msvc在编辑器中添加中文
    // 1、选择工具-选项-文本编辑器-行为-编码->'utf8', '如果是utf8则添加'
    // 2、 编辑-select encoding->'utf8', '按编码保存'
    // 3、需要使用QStringLiteral包裹汉字
    // ui->label_3->setText(QStringLiteral("test测试解决"));
    ui->label_3->setText(QDate::currentDate().toString("yy-MM-dd"));
    QTimer *timer = new QTimer(this);
    timer->start(1000);

    // 显示日期
//    static int hh = 16;
//    static int mm = 17;
//    static int ss = 18;
    connect(timer, &QTimer::timeout,[=](){
        ui->lcdNumber->display(QTime::currentTime().toString("hh:mm:ss"));
//        if(mm>60){
//            mm=0;hh+=1;
//        }
//        if(ss > 60){
//        ss=0;mm+=1;
//        }
//        QString str ;
//        str.sprintf("%02d:%02d:%02d", hh, mm ,ss);
//        ui->lcdNumber->display(QString::number(hh)+':'+QString::number(mm)+':'+QString::number(ss));
//        ui->lcdNumber->display(str);
//        ss +=1;
    });

    QTimer *timer1 = new QTimer(this);
    timer1->start(200);
    QStringList ql = QStringList() << "121°30'E,31°15'N" << "121°31'E,31°16'N" << "121°32'E,31°17'N" << "121°33'E,31°18'N"<< "121°34'E,31°19'N" << "121°33'E,31°20'N"
                                   << "121°33'E,31°21'N" << "121°33'E,31°22'N" << "121°32'E,31°23'N" << "121°33'E,31°24'N"<< "121°34'E,31°25'N" << "121°33'E,31°26'N"
                                   << "121°30'E,31°27'N" << "121°31'E,31°28'N" << "121°32'E,31°29'N" << "121°33'E,31°30'N"<< "121°34'E,31°31'N" << "121°33'E,31°32'N"
                                   << "121°33'E,31°33'N" << "121°33'E,31°34'N" << "121°32'E,31°35'N" << "121°33'E,31°36'N"<< "121°34'E,31°37'N" << "121°33'E,31°38'N"
                                   << "121°30'E,31°15'N" << "121°31'E,31°16'N" << "121°32'E,31°17'N" << "121°33'E,31°18'N"<< "121°34'E,31°19'N" << "121°33'E,31°20'N"
                                   << "121°33'E,31°21'N" << "121°33'E,31°22'N" << "121°32'E,31°23'N" << "121°33'E,31°24'N"<< "121°34'E,31°25'N" << "121°33'E,31°26'N"
                                   << "121°30'E,31°27'N" << "121°31'E,31°28'N" << "121°32'E,31°29'N" << "121°33'E,31°30'N"<< "121°34'E,31°31'N" << "121°33'E,31°32'N"
                                   << "121°33'E,31°33'N" << "121°33'E,31°34'N" << "121°32'E,31°35'N" << "121°33'E,31°36'N"<< "121°34'E,31°37'N" << "121°33'E,31°38'N";

    QStringList ql2 = QStringList() << "121°30'E,31°15'N" << "121°31'E,31°16'N" << "121°32'E,31°17'N" << "121°33'E,31°18'N"<< "121°34'E,31°19'N" << "121°33'E,31°20'N"
                                   << "121°33'E,31°21'N" << "121°33'E,31°22'N" << "121°32'E,31°23'N" << "121°33'E,31°24'N"<< "121°34'E,31°25'N" << "121°33'E,31°26'N"
                                   << "121°30'E,31°27'N" << "121°31'E,31°28'N" << "121°32'E,31°29'N" << "121°33'E,31°30'N"<< "121°34'E,31°31'N" << "121°33'E,31°32'N"
                                   << "121°33'E,31°33'N" << "121°33'E,31°34'N" << "121°32'E,31°35'N" << "121°33'E,31°36'N"<< "121°34'E,31°37'N" << "121°33'E,31°38'N"
                                   << "121°30'E,31°15'N" << "121°31'E,31°16'N" << "121°32'E,31°17'N" << "121°33'E,31°18'N"<< "121°34'E,31°19'N" << "121°33'E,31°20'N"
                                   << "121°33'E,31°21'N" << "121°33'E,31°22'N" << "121°32'E,31°23'N" << "121°33'E,31°24'N"<< "121°34'E,31°25'N" << "121°33'E,31°26'N"
                                  << "121°30'E,31°27'N" << "121°31'E,31°28'N" << "121°32'E,31°29'N" << "121°33'E,31°30'N"<< "121°34'E,31°31'N" << "121°33'E,31°32'N"
                                  << "121°33'E,31°33'N" << "121°33'E,31°34'N" << "121°32'E,31°35'N" << "121°33'E,31°36'N"<< "121°34'E,31°37'N" << "121°33'E,31°38'N";

    QStringList ql3 = QStringList() << "121°30'E,45°15'N" << "121°30'E,45°16'N" <<"121°30'E,45°17'N"<<"121°30'E,45°18'N"<<"121°30'E,45°19'N"<<"121°30'E,45°20'N"
                                    << "121°30'E,45°21'N"<<"121°30'E,45°22'N"<<"121°30'E,45°23'N"<<"121°30'E,45°24'N"<<"121°30'E,45°25'N"<<"121°30'E,45°26'N"
                                    << "121°30'E,45°27'N"<<"121°30'E,45°28'N"<<"121°30'E,45°29'N"<<"121°30'E,45°30'N"<<"121°30'E,45°31'N"<<"121°30'E,45°32'N"
                                    << "121°30'E,45°33'N"<<"121°30'E,45°34'N"<<"121°30'E,45°35'N"<<"121°30'E,45°36'N"<<"121°30'E,45°37'N"<<"121°30'E,45°38'N"
                                    << "121°30'E,45°15'N" << "121°30'E,45°16'N" <<"121°30'E,45°17'N"<<"121°30'E,45°18'N"<<"121°30'E,45°19'N"<<"121°30'E,45°20'N"
                                    << "121°30'E,45°21'N"<<"121°30'E,45°22'N"<<"121°30'E,45°23'N"<<"121°30'E,45°24'N"<<"121°30'E,45°25'N"<<"121°30'E,45°26'N"
                                    << "121°30'E,45°27'N"<<"121°30'E,45°28'N"<<"121°30'E,45°29'N"<<"121°30'E,45°30'N"<<"121°30'E,45°31'N"<<"121°30'E,45°32'N"
                                    << "121°30'E,45°33'N"<<"121°30'E,45°34'N"<<"121°30'E,45°35'N"<<"121°30'E,45°36'N"<<"121°30'E,45°37'N"<<"121°30'E,45°38'N";



    QStringList ql4 = QStringList() << "121°30'E,31°15'N" << "121°31'E,31°16'N" << "121°32'E,31°17'N" << "121°33'E,31°18'N"<< "121°34'E,31°19'N" << "121°33'E,31°20'N"
                                   << "121°33'E,31°21'N" << "121°33'E,31°22'N" << "121°32'E,31°23'N" << "121°33'E,31°24'N"<< "121°34'E,31°25'N" << "121°33'E,31°26'N"
                                   << "121°30'E,31°27'N" << "121°31'E,31°28'N" << "121°32'E,31°29'N" << "121°33'E,31°30'N"<< "121°34'E,31°31'N" << "121°33'E,31°32'N"
                                   << "121°33'E,31°33'N" << "121°33'E,31°34'N" << "121°32'E,31°35'N" << "121°33'E,31°36'N"<< "121°34'E,31°37'N" << "121°33'E,31°38'N"
                                   << "121°30'E,31°15'N" << "121°31'E,31°16'N" << "121°32'E,31°17'N" << "121°33'E,31°18'N"<< "121°34'E,31°19'N" << "121°33'E,31°20'N"
                                  << "121°33'E,31°21'N" << "121°33'E,31°22'N" << "121°32'E,31°23'N" << "121°33'E,31°24'N"<< "121°34'E,31°25'N" << "121°33'E,31°26'N"
                                  << "121°30'E,31°27'N" << "121°31'E,31°28'N" << "121°32'E,31°29'N" << "121°33'E,31°30'N"<< "121°34'E,31°31'N" << "121°33'E,31°32'N"
                                  << "121°33'E,31°33'N" << "121°33'E,31°34'N" << "121°32'E,31°35'N" << "121°33'E,31°36'N"<< "121°34'E,31°37'N" << "121°33'E,31°38'N";


    static int i = 0;
    connect(timer1, &QTimer::timeout,[=](){
        if(i<ql.size())
        {
            ui->widget_1->findChild<QLabel*>("label_2")->setText(ql[i]);
            ui->widget_2->findChild<QLabel*>("label_2")->setText(ql2[i]);
            ui->widget_4->findChild<QLabel*>("label_2")->setText(ql3[i]);
            ui->widget_5->findChild<QLabel*>("label_2")->setText(ql4[i]);
            i += 1;
        }
        else {
            i = 0;
        }
    });

    static int j = 0;
    QTimer *timer3 = new QTimer(this);
    timer3->start(2000);
    connect(timer3, &QTimer::timeout,[=](){
        if(j<5)
        {
            ui->widget_1->findChild<QProgressBar*>("progressBar")->setValue(ui->widget_1->findChild<QProgressBar*>("progressBar")->value()-1);
            ui->widget_2->findChild<QProgressBar*>("progressBar")->setValue(ui->widget_2->findChild<QProgressBar*>("progressBar")->value()-1);
            ui->widget_4->findChild<QProgressBar*>("progressBar")->setValue(ui->widget_4->findChild<QProgressBar*>("progressBar")->value()-1);
            ui->widget_5->findChild<QProgressBar*>("progressBar")->setValue(ui->widget_5->findChild<QProgressBar*>("progressBar")->value()-1);
            j += 1;
        }
        else {
            ui->widget_1->findChild<QProgressBar*>("progressBar")->setValue(90);
            ui->widget_2->findChild<QProgressBar*>("progressBar")->setValue(60);
            ui->widget_4->findChild<QProgressBar*>("progressBar")->setValue(70);
            ui->widget_5->findChild<QProgressBar*>("progressBar")->setValue(30);
            j =0;
        }
    });

}


// 显示背景图
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/background.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}

// 接受js的信息定义的函数， jsMsg用来接收js方面送过来的数据，可以是设备的id
void MainWindow::recieveJsMessage(const QString &jsMsg)
{
    // ui->label_3->setText(jsMsg);
//    sView->show();
//    sView2->show();
    sView3->show();
}

void MainWindow::recievePositionSignal(QString msg)
{
    qDebug() << "##################" <<msg;
    ui->label->setText(msg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

