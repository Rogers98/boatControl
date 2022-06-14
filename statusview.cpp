#include "statusview.h"
#include "ui_statusview.h"

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>

#include <QFile>
#include <QInputDialog>
#include <QDebug>
#include <QWebChannel>

statusView::statusView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statusView)
{
    ui->setupUi(this);
    this->resize(1280, 700);
    setWindowTitle(QStringLiteral("状态框"));


    /*************
     * 引入qt-vlc的代码
     * **************/
    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _player->setVideoWidget(ui->video);

    ui->video->setMediaPlayer(_player);

    connect(ui->btn_play, &QPushButton::clicked, this, &statusView::openUrl);
    connect(ui->tabWidget, &QTabWidget::currentChanged, _player,&VlcMediaPlayer::stop);
//    connect(ui->tabWidget,&QTabWidget::close, _player, &VlcMediaPlayer::stop);


    // 使用QWebChannel使得js和widget交互
    QWebChannel *m_pWebChannel = new QWebChannel(this);
    m_pWebChannel->registerObject(QString("qtui"), this);
    ui->widget_map2->page()->setWebChannel(m_pWebChannel);


    QString htmlPath = QCoreApplication::applicationDirPath() + "/baidumap.html";
    QFile file(htmlPath);
    qDebug() << htmlPath;
    ui->widget_map2->load(QUrl("file:///" + htmlPath));

    // 保持窗口置顶
    Qt::WindowFlags m_flags = windowFlags();
    setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
//    show();
//    this->setAttribute(Qt::WA_DeleteOnClose);
}

statusView::~statusView()
{
    delete _player;
    delete _media;
    delete _instance;
    delete ui;
}

void statusView::openUrl()
{
//    QString url = QInputDialog::getText(this, tr("Open Url"), tr("Enter the URL you want to play"));

//    QString url = "rtmp://58.200.131.2:1935/livetv/cctv4";
    QString url = "/home/rogers/workspace/test1.mp4";
        if (url.isEmpty())
            return;
    _media = new VlcMedia(url, true, _instance);
    _player->open(_media);
}

void statusView::recievePosition(const QString &jsMsg)
{
//    this->setWindowTitle(jsMsg);
    qDebug () << "##################recieve data from js:" << jsMsg;
    send_signal(jsMsg);
}

void statusView::send_signal(const QString &msg)
{
    emit sendMessageToMainWindow(msg);
     qDebug () << "#################emit signal";
}


