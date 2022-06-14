#ifndef STATUSVIEW3_H
#define STATUSVIEW3_H

#include "getserialdata.h"

#include <QWidget>

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

namespace Ui {
class StatusView3;
}

class StatusView3 : public QWidget
{
    Q_OBJECT

public:
    explicit StatusView3(QWidget *parent = nullptr);
    ~StatusView3();

    void setIMUData();
    getSerialData *getData;
    void fromQtCallJs();

private:
    Ui::StatusView3 *ui;

    // 直播视频变量
    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;
    int m_state;

private slots:
    void on_playButton_clicked();
    void on_stopButton_clicked();
public slots:
    void fromJsCallQt();
};

#endif // STATUSVIEW3_H
