#ifndef GETSERIALDATA_H
#define GETSERIALDATA_H

#include <QComboBox>
#include <QPushButton>
#include <QSerialPort>
#include <QWidget>

namespace Ui {
class getSerialData;
}

class getSerialData : public QWidget
{
    Q_OBJECT

public:
    explicit getSerialData(QWidget *parent = nullptr);
    ~getSerialData();

    void initUI();

    QStringList getPortNameList();

    void openPort();
    void doDataHandler(QByteArray BufferData);

    QByteArray getPasteData();
    QByteArray getIMUData();
    void sendControlData(QByteArray data);

    QSerialPort* m_serialPort; //串口类

public slots:
    QByteArray receiveInfo();

private:
    Ui::getSerialData *ui;

    QByteArray ReadData;
    QByteArray PasteData;//位置数据
    QByteArray IMUData;

    QByteArray rubishBoatControlData;
    QStringList m_portNameList;

    QComboBox* m_PortNameComboBox;
    QPushButton* m_OpenPortButton;

};

#endif // GETSERIALDATA_H
