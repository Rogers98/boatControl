#include "attitudewidget.h"
#include "ui_attitudewidget.h"
#include <QPainter>
#include <QDebug>

AttitudeWidget::AttitudeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttitudeWidget)
{
    ui->setupUi(this);
}

AttitudeWidget::~AttitudeWidget()
{
    delete ui;
}

void AttitudeWidget::paintEvent(QPaintEvent *event)
{
    QPainter  painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    /*************************姿态表盘***************************/
    painter.resetTransform();
    painter.translate(245,165);

    QRadialGradient Radial(0,0,165,0,0);    //设置圆的原点和焦点在中心,半径120

    //76,144,181
    Radial.setColorAt(0,QColor(10,124,152,0));
    Radial.setColorAt(0.8,QColor(10,124,152,0));        //设置50%处的半径为蓝色
    Radial.setColorAt(0.95,QColor(10,124,152,55));
    Radial.setColorAt(1,QColor(10,124,152,255));

    painter.setPen(Qt::transparent);
    painter.setBrush(Radial);
    painter.drawEllipse(-165,-165,330,330);
    /**********************
     *
     *        指南针
     *
     * ********************/
    //刻度
    for(int i=0;i<=80;i++)
    {
        painter.setPen(Qt::white);

        //小刻度
        painter.drawLine(0,-158,0,-153);


        //大刻度
        if( i%10==0 )
        {
            //画笔设置
            QPen scale_pen(QColor(10,124,152));
            scale_pen.setWidth(5);
            painter.setPen(scale_pen);
            //画大刻度
            painter.drawLine(0,-158,0,-150);
        }


        painter.rotate(360.0/80.0);
    }

    //画家移动到中间
    painter.resetTransform();
    painter.translate(245,165);


    //字
    static const QString direction_name[] = {
        QString("N"), QString("NE"),
        QString("E"), QString("ES"),
        QString("S"), QString("WS"),
        QString("W"), QString("NW"),
    };
    painter.setFont(QFont("黑体", 15));
    for(int i= 0;i<8;i++)
    {
        painter.drawText(QRect(-20, -158, 40, 40), Qt::AlignCenter, direction_name[i]);

        painter.rotate(45);
    }


    /**********************
     *
     *        姿态盘
     *
     * ********************/

    painter.resetTransform();
    painter.translate(80,0);


    const QRect rectangle = QRect( 45, 45, 240, 240 );

    //底盘
    painter.setBrush(QColor(128,200,27));
    painter.setPen( QColor(128,200,27)) ;
    painter.drawEllipse(rectangle);



    //左右倾斜度   盘
    painter.setBrush( Qt::blue) ;
    painter.setPen( Qt::blue) ;
    //int a = 16* 180 /3.1415 * asin( 3.5* 10 /75);
    //int b = 16* ( 180 - 2 * 180 / 3.1415* asin( 3.5* 20 /75) );
    painter.drawChord( rectangle , 150*16 , -120*16) ;




    QPen scale_pen(Qt::black);
    scale_pen.setWidth(3);

    //左右倾斜度   刻度

    painter.resetTransform();
    painter.translate(245,165);
    painter.setPen(scale_pen);
    painter.scale(400.0/460.0,400.0/460.0);

    //弧
    painter.drawArc( -120 , -120 , 240 , 240 ,  150*16 ,-120*16 );

    //数字
    painter.rotate(-60);
    for(int i = 0;i<=12;i++)
    {
        painter.setFont(QFont("黑体", 9,QFont::Bold));
        painter.drawText(QRect(-10,-215,20,170), Qt::AlignCenter,QString::number(abs(i*10-60)));
        painter.drawLine(0,-110,0,-120);

        painter.rotate(10);
    }


    painter.rotate(-70);
    painter.translate(0,-80);


    //指针
    QPen needl_pen(Qt::red);
    needl_pen.setWidth(2);

    painter.setPen(needl_pen);
    painter.setBrush(Qt::white);

    const QPoint tri_needl[3]=
    {
        QPoint(0,-25),
        QPoint(-10,-15),
        QPoint(10,-15),
    };

    painter.drawPolygon(tri_needl,3);



    /**********************
     *
     *        高度刻度
     *
     * ********************/

    for(int i=1;i<=10;i++)
    {
        if(i%2!=0 && i!=5)
        {
            painter.setPen(scale_pen);
            painter.drawLine(-40,0,40,0);
        }
        else if(i!=5)
        {
            painter.setPen(scale_pen);
            painter.drawLine(-30,0,30,0);
        }
        if(i==5)
        {
            needl_pen.setColor(QColor(76,144,181));
            needl_pen.setWidth(5);

            painter.setPen(needl_pen);
            painter.drawLine(-40,0,40,0);

            painter.drawLine(-120,0,-90,0);
            painter.drawLine(120,0,90,0);

            const QPoint linea[3]=
            {
                QPoint(-35,15),
                QPoint(0,5),
                QPoint(35,15),
            };
            painter.drawPolyline(linea,3);

        }
        painter.translate(0,20);
    }



}
