#ifndef SPEEDWIDGET_H
#define SPEEDWIDGET_H

#include <QWidget>

namespace Ui {
class SpeedWidget;
}

class SpeedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SpeedWidget(QWidget *parent = nullptr);
    ~SpeedWidget();
    void paintEvent(QPaintEvent *event);

private:
    Ui::SpeedWidget *ui;

    //速度
    float now_speed;
};

#endif // SPEEDWIDGET_H
