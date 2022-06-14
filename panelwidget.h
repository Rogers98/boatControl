#ifndef PANELWIDGET_H
#define PANELWIDGET_H

#include <QWidget>

namespace Ui {
class PanelWidget;
}

class PanelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PanelWidget(QWidget *parent = 0);
    ~PanelWidget();
    void paintEvent(QPaintEvent *event);
    void setDeltaAngle (float m_angle);
    float getDeltaAngle ();
    void setNowState (float m_state);
    void setNowSpeed(float msg_speed);
    float getNowSpeed();

private:
    Ui::PanelWidget *ui;

    double now_course;
    double new_course;

    //速度
    float now_speed;

    //键盘按键的变量
    double delta_angle;
    double delta_speed;
    int now_state;
};

#endif // PANEL_H
