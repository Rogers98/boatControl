#ifndef STATUSVIEWRUBBISHBOAT_H
#define STATUSVIEWRUBBISHBOAT_H

#include <QWidget>
#include "getserialdata.h"

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

namespace Ui {
class StatusViewRubbishBoat;
}

class StatusViewRubbishBoat : public QWidget
{
    Q_OBJECT

public:
    explicit StatusViewRubbishBoat(QWidget *parent = nullptr);
    ~StatusViewRubbishBoat();

    void setIMUData();
    getSerialData *getData;
    void fromQtCallJs();

private:
    Ui::StatusViewRubbishBoat *ui;

    // 直播视频变量
    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;
    int m_state;

    // 清洁船的控制数据
    QByteArray rubishBoatControlData;

private slots:
    void on_playButton_clicked();
    void on_stopButton_clicked();
public slots:
    void fromJsCallQt();

protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // STATUSVIEWRUBBISHBOAT_H
