#include "statusviewrubbishboat3.h"
#include "ui_statusviewrubbishboat3.h"

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

#include "QTimer"
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <arpa/inet.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <QVariant>

using namespace std;
//using namespace cv;
//#define SERVER_PORT 8888
//#define BUF_LEN 65535

StatusViewRubbishBoat3::StatusViewRubbishBoat3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusViewRubbishBoat3)
{
    ui->setupUi(this);
    QSplitter* splitterMain = new QSplitter(Qt::Vertical,this);
    splitterMain->setFixedSize(1920, 1013);
    QSplitter* splitterTop = new QSplitter(Qt::Horizontal, splitterMain);

    // 使用QWebChannel使得js和widget交互
    QWebChannel *m_pWebChannel = new QWebChannel(this);
    m_pWebChannel->registerObject(QString("qtui"), this);
    ui->mapWidget->page()->setWebChannel(m_pWebChannel);

    // 载入地图
    //mapWidget->load(QUrl());
    QString htmlPath = QCoreApplication::applicationDirPath() + "/amap5.html"; // 本地的


    QFile file(htmlPath);
    qDebug() << "网页读取成功，路径为：" <<htmlPath;
    ui->mapWidget->load(QUrl("file:///" + htmlPath));
    //    QString htmlPath =  "http://8.129.71.95:1200/amap3.html";
//    ui->mapWidget->load(QUrl(htmlPath));


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

 //   初始化船的控制数据
    rubbishBoatControlData.resize(10);
    rubbishBoatControlData[0] = 0x07;
    rubbishBoatControlData[1] = 0x06;
    rubbishBoatControlData[2] = 0x01;
    rubbishBoatControlData[3] = 0x64;
    rubbishBoatControlData[4] = 0x64;
    rubbishBoatControlData[5] = 0xA0;
    rubbishBoatControlData[6] = 0x01;
    rubbishBoatControlData[7] = 0x64;
    rubbishBoatControlData[8] = 0x64;
    rubbishBoatControlData[9] = 0xA0;
 //   rubbishBoatControlData = rubbishBoatControlData.toHex();
 //   qDebug() << rubbishBoatControlData;


     connect(ui->pushButtonSerial,&QPushButton::clicked,[=]{
         getData = new getSerialData();
         getData->show();
     });

 //    设置船的控制条
     ui->horizontalSlider->setStyleSheet("QSlider::handle:horizontal{width:24px;background-color:rgb(34,110,189);margin:-11px 0px -11px 0px;border-radius:12px;}" //滑块美化
                                         "QSlider::groove:horizontal{height:2px;background-color:rgb(219,219,219);}"  //滑动条槽（整体）的美化
                                         "QSlider::add-page:horizontal{background-color:rgb(219,219,219);}"
                                         "QSlider::sub-page:horizontal{background-color:rgb(219,219,219);}"  //已滑过的进度美化
            );
     ui->verticalSlider->setStyleSheet("QSlider::handle:vertical{height:24px;background-color:rgb(34,110,189);margin: 0px -11px 0px -11px;border-radius:12px;}"
                                         "QSlider::groove:vertical{width:2px;background-color:rgb(219,219,219);}"
                                         "QSlider::add-page:vertical{background-color:rgb(219,219,219);}"
                                         "QSlider::sub-page:vertical{background-color:rgb(219,219,219);}"
            );

     ui->horizontalSlider->setMinimum(0);
     ui->horizontalSlider->setMaximum(200);
     ui->horizontalSlider->setValue(100);
 //    qDebug() << ui->horizontalSlider->value();
     connect(ui->horizontalSlider,&QAbstractSlider::valueChanged,[=](){
 //        qDebug() << ui->horizontalSlider->value();
     });
     ui->horizontalSlider->setSingleStep(1);

     ui->verticalSlider->setMinimum(0);
     ui->verticalSlider->setMaximum(200);
     ui->verticalSlider->setValue(100);



     connect(ui->pushButtonModeSwitchM,&QPushButton::clicked,[=]{  // 手动模式：M
         rubbishBoatControlData[2] = 0x01;
         rubbishBoatControlData[6] = 0x01;
         getData->sendControlData(rubbishBoatControlData);
 //        qDebug() << rubbishBoatControlData.toHex();
         ui->pushButtonModeSwitchM->setStyleSheet("QPushButton{color: rgb(0, 255, 0);}");
         ui->pushButtonModeSwitchH->setStyleSheet("QPushButton{color: rgb(238, 238, 236);}");
         ui->pushButtonModeSwitchD->setStyleSheet("QPushButton{color: rgb(238, 238, 236);}");
     });
     connect(ui->pushButtonModeSwitchH,&QPushButton::clicked,[=]{ //制动模式：Hold
         rubbishBoatControlData[2] = 0x02;
         rubbishBoatControlData[6] = 0x02;
         getData->sendControlData(rubbishBoatControlData);
 //        qDebug() << rubbishBoatControlData.toHex();
         ui->pushButtonModeSwitchM->setStyleSheet("QPushButton{color: rgb(238, 238, 236);}");
         ui->pushButtonModeSwitchH->setStyleSheet("QPushButton{color: rgb(0, 255, 0);}");
         ui->pushButtonModeSwitchD->setStyleSheet("QPushButton{color: rgb(238, 238, 236);}");
     });
     connect(ui->pushButtonModeSwitchD,&QPushButton::clicked,[=]{ // 自动模式：D
         rubbishBoatControlData[2] = 0x03;
         rubbishBoatControlData[6] = 0x03;
         getData->sendControlData(rubbishBoatControlData);
 //        qDebug() << rubbishBoatControlData.toHex();
         ui->pushButtonModeSwitchM->setStyleSheet("QPushButton{color: rgb(238, 238, 236);}");
         ui->pushButtonModeSwitchH->setStyleSheet("QPushButton{color: rgb(238, 238, 236);}");
         ui->pushButtonModeSwitchD->setStyleSheet("QPushButton{color: rgb(0, 255, 0);}");
     });

       // true为前面转， false为前面不转
     connect(ui->pushButtonClearSwitch,&QPushButton::clicked,[=]{
         rubbishBoatControlData[5] = 0xB0;
         rubbishBoatControlData[9] = 0xB0;
         getData->sendControlData(rubbishBoatControlData);
 //            qDebug() << rubbishBoatControlData.toHex();
 //            qDebug() << modeBool;
         ui->pushButtonClearSwitch->setStyleSheet("QPushButton{color: rgb(0, 255, 0);}");
         rubbishBoatControlData[5] = 0xA0;
         rubbishBoatControlData[9] = 0xA0;
         if (modeBool == false) {
             ui->pushButtonClearSwitch->setStyleSheet("QPushButton{color: rgb(0, 255, 0);}");
             modeBool = true;
         } else if (modeBool == true) {
             ui->pushButtonClearSwitch->setStyleSheet("QPushButton{color: rgb(238, 238, 236);}");
             modeBool = false;
         }
     });

     connect(ui->horizontalSlider,&QSlider::sliderMoved,[=](){
 //        qDebug() << ui->horizontalSlider->value();
         if ((unsigned char)rubbishBoatControlData.at(3) < 0xC8 && (unsigned char)rubbishBoatControlData.at(3) >= 0x00) {
             rubbishBoatControlData[3] = ui->horizontalSlider->value();
             rubbishBoatControlData[7] = ui->horizontalSlider->value();
 //            ui->horizontalSlider->setValue((unsigned char)rubbishBoatControlData[3]);
             getData->sendControlData(rubbishBoatControlData);
             qDebug() << rubbishBoatControlData.toHex();
         }
     });
     connect(ui->verticalSlider,&QSlider::sliderMoved,[=](){
 //        qDebug() << ui->horizontalSlider->value();
         if ((unsigned char)rubbishBoatControlData.at(4) < 0xC8 && (unsigned char)rubbishBoatControlData.at(4) >= 0x00) {
             rubbishBoatControlData[4] = ui->horizontalSlider->value();
             rubbishBoatControlData[8] = ui->horizontalSlider->value();
 //            ui->horizontalSlider->setValue((unsigned char)rubbishBoatControlData[3]);
 //            qDebug() << rubbishBoatControlData.toHex();
             getData->sendControlData(rubbishBoatControlData);
         }
     });

 //    QTimer *timer = new QTimer(this);
 //    timer->start(100);
 //    connect(ui->pushButton_4, &QPushButton::clicked,[=](){
 //        getData->receiveInfo();

 //    });

     QTimer *virtualDataTimer = new QTimer(this);
     virtualDataTimer->start(100);
     connect(virtualDataTimer,&QTimer::timeout,[=]() {
        float speed = 3 + ((qrand() % 20)*0.1);
        ui->widget_7->updateValue(speed);
        float yaw = 90 + ((qrand() % 1000) * 0.0001);
        float accX = 1 + ((qrand() % 1000) * 0.0001);
        float accY = -1 + ((qrand() % 1000) * 0.0001);
        float accZ = 0 + ((qrand() % 1000) * 0.0001);
        ui->yaw_label->setNum(yaw);
        ui->ax_label->setNum(accX);
        ui->ay_label->setNum(accY);
        ui->az_label->setNum(accZ);
     });

 //    recvFile.setFileName("Data.csv");
     connect(ui->pushButton_11, &QPushButton::clicked, [=]() {
         rubbishBoatControlData.resize(8);
         rubbishBoatControlData[0] = 0x07;
         rubbishBoatControlData[1] = 0x06;
         rubbishBoatControlData[2] = 0x01;
         rubbishBoatControlData[3] = 0x64;
         rubbishBoatControlData[4] = 0x64;
         rubbishBoatControlData[5] = 0xA0;
         rubbishBoatControlData[6] = 0x01;
         rubbishBoatControlData[7] = 0x64;
         rubbishBoatControlData[8] = 0x64;
         rubbishBoatControlData[9] = 0xA0;
         ui->verticalSlider->setValue((unsigned char)rubbishBoatControlData[4]);
         ui->horizontalSlider->setValue((unsigned char)rubbishBoatControlData[3]);
         getData->sendControlData(rubbishBoatControlData);
     });

}

StatusViewRubbishBoat3::~StatusViewRubbishBoat3()
{
    delete ui;
}

void StatusViewRubbishBoat3::on_playButton_clicked()
{

    /********socket播放*******/
//    playVideo();

    /****rtsp拉流方式||本地视频播放*****/
//    if (libvlc_Ended == libvlc_media_get_state(_media))
    QString url = ui->videoAddEdit->text();

    // 地址1：/home/rogers/workspace/test1.mp4
    // 地址2：rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov
    // 地址3：http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8
    // 地址4：rtmp://58.200.131.2:1935/livetv/cctv1
    if (url.isEmpty())
    {
//        QMessageBox::information(NULL, "提示", "地址为空，默认播放测试视频", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
        _media = new VlcMedia("/home/rogers/workspace/test3.mp4", true, _instance);
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

void StatusViewRubbishBoat3::on_stopButton_clicked()
{
//    _player->stop();
}

void StatusViewRubbishBoat3::on_pushButton_4_clicked()
{
    connect(getData->m_serialPort,SIGNAL(readyRead()),this,SLOT(recvDataFromSerial()));
}

void StatusViewRubbishBoat3::fromJsCallQt()
{
    qDebug() << "qt:来自html的调用";
    this->fromQtCallJs();

}

void StatusViewRubbishBoat3::fromQtCallJs() {
    QString x1="113.395774", y1="23.034974", x2="113.39579", y2="23.035616";
    QString jsStr = "drawPositionLine(" + x1 + "," + y1 + "," + x2 + "," + y2 +")";
    qDebug() << jsStr;
    ui->mapWidget->page()->runJavaScript(jsStr);
}

void StatusViewRubbishBoat3::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_D) {
        if ((unsigned char)rubbishBoatControlData.at(3) < 0xC8 && (unsigned char)rubbishBoatControlData.at(3) >= 0x00) {
            rubbishBoatControlData[3] = rubbishBoatControlData[3] + 1;
            rubbishBoatControlData[7] = rubbishBoatControlData[7] + 1;
            ui->horizontalSlider->setValue((unsigned char)rubbishBoatControlData[3]);
            qDebug() << rubbishBoatControlData.toHex();
        }
    } else if (event->key() == Qt::Key_A) {
        if ((unsigned char)rubbishBoatControlData.at(3) <= 0xC8 && (unsigned char)rubbishBoatControlData.at(3) > 0x00) {
            rubbishBoatControlData[3] = rubbishBoatControlData[3] - 1;
            rubbishBoatControlData[7] = rubbishBoatControlData[7] - 1;
            ui->horizontalSlider->setValue((unsigned char)rubbishBoatControlData[3]);
            qDebug() << rubbishBoatControlData.toHex();
        }
    } else if (event->key() == Qt::Key_S) {
        if ((unsigned char)rubbishBoatControlData.at(4) <= 0xC8 && (unsigned char)rubbishBoatControlData.at(4) > 0x00) {
            rubbishBoatControlData[4] = rubbishBoatControlData[4] - 1;
            rubbishBoatControlData[8] = rubbishBoatControlData[8] - 1;
            ui->verticalSlider->setValue((unsigned char)rubbishBoatControlData[4]);
            qDebug() << rubbishBoatControlData.toHex();
        }
    } else if (event->key() == Qt::Key_W) {
        if ((unsigned char)rubbishBoatControlData.at(4) < 0xC8 && (unsigned char)rubbishBoatControlData.at(4) >= 0x00) {
            rubbishBoatControlData[4] = rubbishBoatControlData[4] + 1;
            rubbishBoatControlData[8] = rubbishBoatControlData[8] + 1;
            ui->verticalSlider->setValue((unsigned char)rubbishBoatControlData[4]);
            qDebug() << rubbishBoatControlData.toHex();
        }
    } else if (event->key() == Qt::Key_Space) {
        rubbishBoatControlData.resize(8);
        rubbishBoatControlData[0] = 0x07;
        rubbishBoatControlData[1] = 0x06;
        rubbishBoatControlData[2] = 0x01;
        rubbishBoatControlData[3] = 0x64;
        rubbishBoatControlData[4] = 0x64;
        rubbishBoatControlData[5] = 0xA0;
        rubbishBoatControlData[6] = 0x01;
        rubbishBoatControlData[7] = 0x64;
        rubbishBoatControlData[8] = 0x64;
        rubbishBoatControlData[9] = 0xA0;
        ui->verticalSlider->setValue((unsigned char)rubbishBoatControlData[4]);
        ui->horizontalSlider->setValue((unsigned char)rubbishBoatControlData[3]);
    }

    getData->sendControlData(rubbishBoatControlData);
}


/*void StatusViewRubbishBoat3::playVideo() {
    //socket配置
        int ServerFd;
        char Buf[BUF_LEN] = {0};
        struct sockaddr ClientAddr;
        struct sockaddr_in  ServerSockAddr;
        socklen_t addr_size = 0;

//         创建服务端socket
        if (-1 == (ServerFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)))
        {
            printf("socket error!\n");
            exit(1);
        }

//         向服务器发起请求
        memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
        ServerSockAddr.sin_family = AF_INET;
        ServerSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        ServerSockAddr.sin_port = htons(SERVER_PORT);

//         绑定套接字
        if (-1 == (bind(ServerFd, (struct sockaddr*)&ServerSockAddr, sizeof(struct sockaddr))))
        {
            printf("bind error!\n");
            exit(1);
        }

        addr_size = sizeof(struct sockaddr);

        cv::Mat image;
        char buf[655360];

        int recvNums = 1;
        while (recvNums > 0)
        {
//            qDebug() << "进来了#########################";
            std::vector<uchar> decode;
//             接收客户端的返回数据
            recvNums = ::recvfrom(ServerFd, buf, sizeof(buf), 0, &ClientAddr, &addr_size);
//            printf("客户端发送过来的数据为：%s\n", Buf);
            int pos = 0;
            while (pos < recvNums)
            {
                decode.push_back(buf[pos++]);//存入vector
            }
            if (recvNums > 0)
            {
                buf[recvNums] = 0;
                image = cv::imdecode(decode, CV_LOAD_IMAGE_COLOR);//图像解码
                if (image.empty())    //如果照片为空则退出
                {
                    printf("empty image\n");
                    rubbishBoatControlData[0] = 0x07;
                    rubbishBoatControlData[1] = 0x06;
                    rubbishBoatControlData[2] = 0x01;
                    rubbishBoatControlData[3] = 0x64;
                    rubbishBoatControlData[4] = 0x64;
                    rubbishBoatControlData[5] = 0xA0;
                    rubbishBoatControlData[6] = 0x01;
                    rubbishBoatControlData[7] = 0x64;
                    rubbishBoatControlData[8] = 0x64;
                    rubbishBoatControlData[9] = 0xA0;
                    getData->sendControlData(rubbishBoatControlData);
                    ::close(ServerFd);   // 关闭套接字
                    break ;
                }
                else
                {
//                    imshow("image", image);
//                    LabelDisplayMat(ui->videoPlayWidget, image);
                    try{
                        LabelDisplayMat(ui->videoPlayWidget, image);
                    } catch(...) {
                        rubbishBoatControlData[0] = 0x07;
                        rubbishBoatControlData[1] = 0x06;
                        rubbishBoatControlData[2] = 0x01;
                        rubbishBoatControlData[3] = 0x64;
                        rubbishBoatControlData[4] = 0x64;
                        rubbishBoatControlData[5] = 0xA0;
                        rubbishBoatControlData[6] = 0x01;
                        rubbishBoatControlData[7] = 0x64;
                        rubbishBoatControlData[8] = 0x64;
                        rubbishBoatControlData[9] = 0xA0;
                        getData->sendControlData(rubbishBoatControlData);
                    }

                    if (cv::waitKeyEx(3)==27)
                    {
                        break;//跳出整个while大循环
                    }

                }

            }
            if (recvNums <= 0)
            {
                qDebug() << "#####################" << recvNums;
                rubbishBoatControlData[0] = 0x07;
                rubbishBoatControlData[1] = 0x06;
                rubbishBoatControlData[2] = 0x01;
                rubbishBoatControlData[3] = 0x64;
                rubbishBoatControlData[4] = 0x64;
                rubbishBoatControlData[5] = 0xA0;
                rubbishBoatControlData[6] = 0x01;
                rubbishBoatControlData[7] = 0x64;
                rubbishBoatControlData[8] = 0x64;
                rubbishBoatControlData[9] = 0xA0;
                getData->sendControlData(rubbishBoatControlData);
                ::close(ServerFd);   // 关闭套接字
                break;
            }
//             清空缓冲区
            memset(buf, 0, sizeof(buf));


        }
        qDebug() << "chulai了*************************";

       ::close(ServerFd);   // 关闭套接字
}

//参数1-显示图像的Label，参数2-要显示的Mat
void StatusViewRubbishBoat3::LabelDisplayMat(QLabel *label, cv::Mat &mat)
{
    cv::Mat Rgb;
    QImage Img;
    if (mat.channels() == 3)//RGB Img
    {
        cv::cvtColor(mat, Rgb, CV_BGR2RGB);//颜色空间转换
        Img = QImage((const uchar*)(Rgb.data), Rgb.cols, Rgb.rows, Rgb.cols * Rgb.channels(), QImage::Format_RGB888);
    }
    else//Gray Img
    {
        Img = QImage((const uchar*)(mat.data), mat.cols, mat.rows, mat.cols*mat.channels(), QImage::Format_Indexed8);
    }
    label->setPixmap(QPixmap::fromImage(Img));
}*/


void StatusViewRubbishBoat3::setRecvDataView(QByteArray data){
//    rubbishBoatRecvData = getData->receiveInfo();
    qDebug() << data.toHex();
    float accXArray[4];
    float accYArray[4];
    float accZArray[4];
    float gyrXArray[4];
    float gyrYArray[4];
    float gyrZArray[4];
    float pitchArray[4];
    float rollArray[4];
    float yawArray[4];
    float lngArray[4];
    float latArray[4];
    memcpy(accXArray, data.mid(0, 4), 4);  // 必要时进行reverse
    memcpy(accYArray, data.mid(4, 4), 4);
    memcpy(accZArray, data.mid(8, 4), 4);
    memcpy(gyrXArray, data.mid(12, 4), 4);
    memcpy(gyrYArray, data.mid(16, 4), 4);
    memcpy(gyrZArray, data.mid(20, 4), 4);
    memcpy(pitchArray, data.mid(24, 4), 4);
    memcpy(rollArray, data.mid(28, 4), 4);
    memcpy(yawArray, data.mid(32, 4), 4);
    memcpy(lngArray, data.mid(37, 4), 4);
    memcpy(latArray, data.mid(42, 4), 4);
    accX = *(float *) accXArray;
    accY = *(float *) accYArray;
    accZ = *(float *) accZArray;
    gyrX = *(float *) gyrXArray;
    gyrY = *(float *) gyrYArray;
    gyrZ = *(float *) gyrZArray;
    pitch = *(float *) pitchArray;
    roll = *(float *) rollArray;
    yaw = *(float *) yawArray;
    lng = *(float *) lngArray;
    lat = *(float *) latArray;

    ui->ax_label->setNum(accX);
    ui->ay_label->setNum(accY);
    ui->az_label->setNum(accZ);
    ui->yaw_label->setNum(yaw);

//    qDebug() << accXArray << "," << accX;
//    qDebug() << pitch;
//    qDebug() << lngArray << "," << latArray;
//    qDebug() << QString::number(lng, 'f', 6) << "," << QString::number(lat, 'f', 6);

//    QFile file2("test.csv"); //收集数据
//    if(file2.open(QIODevice::Append)) {

//        QTextStream out(&file2);
//        out << lng << "," << lat << "\n";
//    } else {
//        qDebug() << "open fial";
//    }
//    file2.close();

}

void StatusViewRubbishBoat3::recvDataFromSerial() {
    QByteArray recvData = getData->receiveInfo();  // 获取串口拿到的数据

//    QFile file2("test.csv"); //收集数据

//        if(recvFile.open(QIODevice::Append)) {

//            QTextStream out(&recvFile);
//            out << recvData.toHex()<< "\n";
//        } else {
//            qDebug() << "open fial";
//        }

    qDebug() << recvData.toHex();
    setRecvDataView(recvData); // 开始设置界面
}
