#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "statusview.h"
#include "statusview2.h"
#include "statusview3.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    statusView *sView;
    StatusView2 *sView2;
    StatusView3 *sView3;

//    statusView *ss;

private:
    Ui::MainWindow *ui;

public slots:
    void recieveJsMessage(const QString &jsMsg);
    void recievePositionSignal(QString msg);

};
#endif // MAINWINDOW_H
