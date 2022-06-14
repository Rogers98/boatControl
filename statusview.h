#ifndef STATUSVIEW_H
#define STATUSVIEW_H

#include <QWidget>

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

namespace Ui {
class statusView;
}

class statusView : public QWidget
{
    Q_OBJECT

public:
    explicit statusView(QWidget *parent = nullptr);
    ~statusView();
    Ui::statusView *ui;

    void send_signal(const QString &msg);
private:


    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;

private slots:
    void openUrl();

public slots:
    void recievePosition(const QString &jsMsg);
//    void stopUrl();

signals:
    void sendMessageToMainWindow(QString msg);
};

#endif // STATUSVIEW_H
