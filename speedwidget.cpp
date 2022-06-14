#include "speedwidget.h"
#include "ui_speedwidget.h"
#include <QPainter>

SpeedWidget::SpeedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpeedWidget)
{
    ui->setupUi(this);

    this->now_speed = 0;

//    setStyleSheet("QWidget{background-color:black}");


}

SpeedWidget::~SpeedWidget()
{
    delete ui;
}

void SpeedWidget::paintEvent(QPaintEvent *event)
{
    QPainter  painter(this);

    //painter.save();
    painter.setRenderHint(QPainter::Antialiasing);

    /*************************速度表盘***************************/

    painter.translate(245,165);

    /*************************
     *********  外框  *********
     * **********************/
    //渐变
    QRadialGradient Radial(0,0,165,0,0);    //设置圆的原点和焦点在中心,半径120

    //76,144,181
    Radial.setColorAt(0,QColor(10,124,152,0));
    Radial.setColorAt(0.8,QColor(10,124,152,0));        //设置50%处的半径为蓝色
    Radial.setColorAt(0.95,QColor(10,124,152,55));
    Radial.setColorAt(1,QColor(10,124,152,255));

    painter.setPen(Qt::transparent);
    painter.setBrush(Radial);
    painter.drawEllipse(-165,-165,330,330);

    painter.translate(650,0);
    painter.drawEllipse(-165,-165,330,330);

    //中心红点
    painter.resetTransform();
    painter.translate(245,165);

    painter.setPen(Qt::red);
    painter.setBrush(Qt::white);

    for(float i = 0; i <= 45 ; i++ )
    {
        painter.rotate(8);
        painter.drawEllipse(0,-85,5,5);
    }

    //初始化
    painter.resetTransform();
    painter.translate(245,165);

    //中心盘刻度
    painter.setPen(Qt::white);
    painter.rotate(-120);
    for(int i=0; i <= 80 ; i++)
    {
        painter.drawLine(0,-157.5,0,-152.5);
        painter.rotate(3);
    }

    //大刻度
    painter.resetTransform();
    painter.translate(245,165);
    painter.rotate(-150);

    QPen speed_pen;
    speed_pen.setColor(QColor(10,124,152,255));
    speed_pen.setWidth(5);

    for(int j=0; j<= 20; j++)
    {
        painter.setPen(speed_pen);
        painter.drawLine(0,-160,0,-150);

        painter.setPen(Qt::white);
        painter.setFont(QFont("黑体",12));
        painter.drawText(QRect( -15 , -145 , 30, 15), Qt::AlignCenter, QString::number( j* 20));

        painter.rotate(15);
    }

    painter.resetTransform();
    painter.translate(245,165);


    //指针
    painter.rotate(this->now_speed/20*15-150);
    QPixmap pix1;
    pix1.load(":/res/指针.png");
    painter.drawPixmap(-20,-120,40,30,pix1);

/*************************速度表盘***************************/
}
