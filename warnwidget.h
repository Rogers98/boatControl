#ifndef WARNWIDGET_H
#define WARNWIDGET_H

#include <QWidget>

namespace Ui {
class WarnWidget;
}

class WarnWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WarnWidget(QWidget *parent = nullptr);
    ~WarnWidget();
    void paintEvent(QPaintEvent * event);

private:
    Ui::WarnWidget *ui;
};

#endif // WARNWIDGET_H
