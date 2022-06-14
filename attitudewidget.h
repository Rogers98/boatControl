#ifndef ATTITUDEWIDGET_H
#define ATTITUDEWIDGET_H

#include <QWidget>

namespace Ui {
class AttitudeWidget;
}

class AttitudeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AttitudeWidget(QWidget *parent = nullptr);
    ~AttitudeWidget();
    void paintEvent(QPaintEvent *event);

private:
    Ui::AttitudeWidget *ui;
};

#endif // ATTITUDEWIDGET_H
