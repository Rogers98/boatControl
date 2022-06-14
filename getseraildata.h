#ifndef GETSERAILDATA_H
#define GETSERAILDATA_H

#include <QByteArray>
#include <QSerialPort>



class getSerailData
{
private:
    QByteArray ReadData;
    QByteArray PasteData;//位置数据
    QByteArray IMUData;//IMU数据

    QSerialPort* m_serialPort; //串口类
    QStringList m_portNameList;

public:
    getSerailData();
    QStringList getPortNameList();

    void openPort();
    void doDataHandler(QByteArray BufferData);
    QByteArray getPasteData();
    QByteArray getIMUData();

public slots:
    void receiveInfo();
};

#endif // GETSERAILDATA_H
