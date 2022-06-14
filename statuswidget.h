#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>

namespace Ui {
class StatusWidget;
}

class StatusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatusWidget(QWidget *parent = nullptr);
    ~StatusWidget();
    void paintEvent(QPaintEvent * event);

private:
    Ui::StatusWidget *ui;
};

#endif // STATUSWIDGET_H
