#include "getserialdata.h"
#include "ui_getserialdata.h"


#include <QLayout>
#include <QSerialPortInfo>
#include <QDebug>

getSerialData::getSerialData(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::getSerialData)
{
    ui->setupUi(this);

    m_serialPort = new QSerialPort();

    initUI();

    m_portNameList = getPortNameList();

    m_PortNameComboBox->addItems(m_portNameList);

    connect(m_OpenPortButton,&QPushButton::clicked,this,&getSerialData::openPort);

    rubishBoatControlData.resize(8);
    rubishBoatControlData[0] = 0x07;
    rubishBoatControlData[1] = 0x06;
    rubishBoatControlData[2] = 0x64;
    rubishBoatControlData[3] = 0x88;
    rubishBoatControlData[4] = 0xA0;
    rubishBoatControlData[5] = 0x64;
    rubishBoatControlData[6] = 0x88;
    rubishBoatControlData[7] = 0xA0;

//    connect(ui->pushButton,&QPushButton::clicked,this,&getSerialData::sendControlData);



}

getSerialData::~getSerialData()
{
    if (m_serialPort->isOpen())
    {
        m_serialPort->close();
    }
    delete m_serialPort;
    delete ui;
}


void getSerialData::initUI()
{
    this->setWindowTitle("test QSerialPort");


    m_OpenPortButton = new QPushButton();
    m_OpenPortButton->setText("打开串口");

    m_PortNameComboBox  = new QComboBox();

    QHBoxLayout *m_layout = new QHBoxLayout();

    m_layout->addWidget(m_PortNameComboBox);
    m_layout->addWidget(m_OpenPortButton);

    this->setLayout(m_layout);
}

QStringList getSerialData::getPortNameList()
{
    QStringList m_serialPortName;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        m_serialPortName << info.portName();
        qDebug()<<"serialPortName:"<<info.portName();
    }
    return m_serialPortName;
}

void getSerialData::openPort()
{
    if(m_serialPort->isOpen())//如果串口已经打开了 先给他关闭了
    {
        m_serialPort->clear();
        m_serialPort->close();
    }


    m_serialPort->setPortName(m_PortNameComboBox->currentText());//当前选择的串口名字
//    m_serialPort->setPortName("/dev/ttyUSB1");
//    m_serialPort->setPortName("/dev/ttyUSB0");

    if(!m_serialPort->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
    {
        qDebug()<<"打开失败!";
        return;
    }
    qDebug()<<"串口打开成功!";

    m_serialPort->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);//设置波特率和读写方向
    m_serialPort->setDataBits(QSerialPort::Data8);      //数据位为8位
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    m_serialPort->setParity(QSerialPort::NoParity); //无校验位
    m_serialPort->setStopBits(QSerialPort::OneStop); //一位停止位

//    connect(m_serialPort,SIGNAL(readyRead()),this,SLOT(receiveInfo()));

    this->close();
}

//接收到单片机发送的数据进行解析
QByteArray getSerialData::receiveInfo()
{
    QByteArray temp = m_serialPort->readAll();

//    qDebug() << "第"<< count << "次数据:" << temp.toHex() ;

    static QByteArray sumData;
//    static int count = 0;
    sumData.resize(46);
    if (temp.size()==24) {
        sumData.replace(0, 24, temp);
    }else if (temp.size()==22) {
        sumData.replace(24,22,temp);
    }

    /*
//    static QByteArray preData;
//    preData.resize(46);

//    if (temp.size()==24) {
//        sumData.mid()
//    }
//    if(!temp.isEmpty())
//    {
//        sumData.append(temp);
////        if(sumData.contains("\n"))
////        {
//            doDataHandler(sumData);
//            sumData.clear();
////        }
//    }
//    temp.clear();*/


//    qDebug()<<"receive info:"<<info;

//    if(!temp.isEmpty()) {
//        if(temp.size()== 24 && sumData.isEmpty()) {
//            sumData.append(temp);
//        } else if (temp.size() == 22 && sumData.size() == 24) {
//            sumData.append(temp);
//        } else {
//            sumData.clear();
//        }
//    }
    temp.clear();

//    qDebug() << "recieveData" << count << ": " << sumData.toHex();
    return sumData;
}

void getSerialData::doDataHandler(QByteArray BufferData)
{
    //未定义帧数据长度时的处理方法
//    //异常类：无头且变量为空，已丢失头部，数据不可靠，直接返回
//        if ((!BufferData.contains("Y"))&(PasteData.isNull()))
//        {
//            return;
//        }
//        //第一种：有头无尾，先清空原有内容，再附加
//        if ((BufferData.contains("Y"))&(!BufferData.contains("E")))
//        {
//            PasteData.clear();
//            PasteData.append(BufferData);
//        }
//        //第二种：无头无尾且变量已有内容，数据中段部分，继续附加即可
//        if ((!BufferData.contains("Y"))&(!BufferData.contains("E"))&(!PasteData.isNull()))
//        {
//            PasteData.append(BufferData);
//        }
//        //第三种：无头有尾且变量已有内容，已完整读取，附加后输出数据，并清空变量
//        if ((!BufferData.contains("Y"))&(BufferData.contains("E"))&(!PasteData.isNull()))
//        {
//            PasteData.append(BufferData);
//            ReadData = PasteData;
//            PasteData.clear();
//        }
//        //第四种：有头有尾（一段完整的内容），先清空原有内容，再附加，然后输出，最后清空变量
//        if ((BufferData.contains("Y"))&(BufferData.contains("E")))
//        {
//            PasteData.clear();
//            PasteData.append(BufferData);
//            ReadData = PasteData;

//            PasteData.clear();
//        }



//        if(BufferData.count("Z")>=2)
//            return;
//        //异常类：无头且变量为空，已丢失头部，数据不可靠，直接返回
//        if( BufferData.contains("Z"))
//        {
//            IMUData = BufferData;
//        }
////        qDebug() << IMUData;
//        if (ReadData.length()>0)
//        {
////            qDebug() << "ReadData:" << ReadData.data();
//////            qDebug() << ReadData.mid(10, 6);
////            qDebug() << "IMUData:" << IMUData.data();
//        }
////        ReadData.clear();
//    qDebug() << "接受到的数据:" << BufferData.toHex() ;
//    count += 1;

}


QByteArray getSerialData::getIMUData()
{
    return IMUData;
}

void getSerialData::sendControlData(QByteArray boatData)
{
    // 测试时端口没有打开发送，回闪退，在这里注释了
//    qDebug() << boatData;
//    m_serialPort->write(boatData);
//    //m_serialPort->write(rubishBoatControlData);
}
